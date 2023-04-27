package main

// import "fmt"
import "testing"
import "errors"

var ErrItemNotFound = errors.New("Item not exists")

type LRUCache interface {
	Add(key string, item any)
	// returns ErrItemNotFound when there is no item found for given key.
	Get(key string) (any, error)
}

type lruCache struct {
	cache map[string]*listItem
	accessList list
	capacity int
}

// doubly linked list
type listItem struct {
	key string
	value any
	prev *listItem
	next *listItem
}

type list struct {
	head *listItem
	tail *listItem
}

func newList() list {
	return list {}
}

func (l *list) insert(item *listItem) {
	// empty list
	if l.head == nil {
		l.head = item
		l.tail = item
	} else { // list with existing items
		oldHead := l.head
		l.head = item
		item.next = oldHead
		oldHead.prev = item
	}
}

func (l *list) remove(item *listItem) {
	switch {
		case l.head == item && l.tail == item:
			l.head = nil
			l.tail = nil
		case l.head == item:
			newHead := l.head.next
			newHead.prev = nil
			l.head = newHead
		case l.tail == item:
			newTail := l.tail.prev
			newTail.next = nil
			l.tail = newTail
		default:
			prev := item.prev
			next := item.next
			prev.next = next
			next.prev = prev
	}
}

func (l *list) first() *listItem {
	return l.head
}

func (l *list) last() *listItem {
	return l.tail
}

func NewLRUCache(capacity int) *lruCache {
	return &lruCache {
		cache: map[string]*listItem {},
		accessList: newList(),
		capacity: capacity,
	}
}

func (c *lruCache) Size() int {
	return len(c.cache)
}

func (c *lruCache) evict() *listItem {
	last := c.accessList.last()
	c.accessList.remove(last)
	delete (c.cache, last.key)
	return last
}

func (c *lruCache) Add(key string, value any) {
	var cacheItem *listItem
	if len(c.cache) >= c.capacity {
		// reuse evicted node for better
		// allocation efficiency.
		cacheItem = c.evict()
		cacheItem.next = nil
		cacheItem.prev = nil
	} else {
		cacheItem = new(listItem)
	}
	cacheItem.key = key
	cacheItem.value = value
	c.accessList.insert(cacheItem)
	c.cache[key] = cacheItem
}

func (c *lruCache) Get(key string) (any, error) {
	listItem, ok := c.cache[key]
	if !ok {
		return nil, ErrItemNotFound
	}
	// recently accessed item must be always in the begining
	// of the accessList
	c.accessList.remove(listItem)
	c.accessList.insert(listItem)
	return listItem.value, nil
}


func TestLRUCache(t *testing.T) {
	type readholder struct{}
	type items [2]any

	tt := []struct {
		Name string
		Size int
		Items []items
		ExpectedItems []items
	} {
		{
			Name: "Empty cache",
			Size: 0,
		},
		{
			Name: "Cache with size 1",
			Size: 1,
			Items: []items {
				{"hello", "world"},
			},
			ExpectedItems: []items {
				{"hello", "world"},
			},
		},
		{
			Name: "Cache with mising item",
			Size: 0,
			ExpectedItems: []items {
				{"hello", ErrItemNotFound},
			},
		},
		{
			Name: "Cache with size 1 and check eviction",
			Size: 1,
			Items: []items {
				{"hello", "world",},
				{"foo", "bar",},
			},
			ExpectedItems: []items {
				{"hello", ErrItemNotFound,},
				{"foo", "bar",},
			},
		},
		{
			Name: "Cache with size 1 and insert more",
			Size: 1,
			Items: []items {
				{"hello", "world",},
				{"foo", "bar",},
				{"bob", "bar",},
				{"lisa", "bar",},
			},
			ExpectedItems: []items {
				{"bob", ErrItemNotFound,},
				{"lisa", "bar",},
			},
		},
		{
			Name: "Read firstly inserted item to avoid evition",
			Size: 2,
			Items: []items {
				{"hello", "world",},
				{"foo", "bar",},
				{"hello", readholder{},},
				{"lisa", "bar",},
			},
			ExpectedItems: []items {
				{"foo", ErrItemNotFound,},
				{"hello", "world",},
				{"lisa", "bar",},
			},
		},
	}
	for _, tc := range tt {
		t.Run(tc.Name, func(t *testing.T) {
			cache := NewLRUCache(tc.Size)
			for _, item := range tc.Items {
				k, v := item[0].(string), item[1]
				switch v.(type) {
					// simulates read
					case readholder:
						cache.Get(k)
					case any:
						cache.Add(k, v)
				}
			}

			for _, item := range tc.ExpectedItems {
				k, v := item[0].(string), item[1]
				actual, err := cache.Get(k)
				if tc.Size != cache.Size() {
					t.Errorf("Unexpected size: %d, expected: %d", cache.Size(), tc.Size)
				}
				switch v.(type) {
					case string:
						val := actual.(string)
						expectedVal := v.(string)
						if val != expectedVal {
							t.Errorf("Expected: %s, actual: %s", expectedVal, val)
						}
					case error:
						expectedVal := v.(error)
						if err != expectedVal {
							t.Errorf("Expected: %s, actual: %s, value: %s", expectedVal, err, actual)
						}
			}
		}
		})
	}
}

func TestDoublyLinkedList(t *testing.T) {
	l := newList()
	for i := 0; i < 10; i++ {
		i0 := &listItem{}
		l.insert(i0)
		if l.first() != i0 {
			t.Errorf("expected: %v, actual: %v", i0, l.first())
		}
		if l.last() != i0 {
			t.Errorf("expected: %v, actual: %v", i0, l.last())
		}
		l.remove(i0)
		i1 := &listItem{}
		l.insert(i1)
		if l.first() != i1 {
			t.Errorf("expected: %v, actual: %v", i1, l.first())
		}
		l.remove(i1)
		if l.first() != nil || l.last() != nil {
			t.Error("list must be empty")
		}
	}
}

