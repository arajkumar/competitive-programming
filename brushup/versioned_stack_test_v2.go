package main

import "testing"
import "errors"

var ErrNoVersionFound = errors.New("No version found")
var ErrEmptyStack = errors.New("Stack is empty")

type Version int

type StackNode struct {
	Element int
	Version Version
	Prev    *StackNode
}

type Stack struct {
	Top     *StackNode
	CurrentVersion Version
	Versions map[Version]*StackNode
}

func NewStack() *Stack {
	return &Stack{
		Top:     nil,
		Versions: map[Version]*StackNode{},
	}
}

func (s *Stack) Push(element int) Version {
	s.CurrentVersion ++
	newNode := &StackNode{
		Element: element,
		Version: s.CurrentVersion,
		Prev:    s.Top,
	}
	s.Top = newNode
	s.Versions[s.CurrentVersion] = newNode
	return s.CurrentVersion
}

func (s *Stack) Pop() (Version, error) {
	if s.Top == nil {
		return -1, ErrEmptyStack
	}
	s.CurrentVersion ++
	s.Versions[s.CurrentVersion] = s.Top.Prev
	s.Top = s.Top.Prev
	return s.CurrentVersion, nil
}
func (s *Stack) AsArray(version Version) ([]int, error) {
	versionNode, ok := s.Versions[version]
	if !ok  {
		return nil, ErrNoVersionFound
	}

	// Find depth of the stack to pre allocate array
	depth := 0
	node := versionNode
	for node != nil {
		depth ++
		node = node.Prev
	}
	node = versionNode
	elements := make([]int, depth)
	for node != nil {
		depth --
		// Fill from the end to form an order
		elements[depth] = node.Element
		node = node.Prev
	}
	return elements, nil
}

func TestErrEmptyStack(t* testing.T) {
	s := NewStack()
	_, err := s.Pop()
	if err != ErrEmptyStack {
		t.Errorf("Expected: %s, Got: %s", ErrEmptyStack, err)
	}
	s.Push(1)
	s.Push(2)
	_, err = s.Pop()
	if err != nil {
		t.Errorf("Expected err: %s", err)
	}
	s.Pop()
	_, err = s.Pop()
	if err != ErrEmptyStack {
		t.Errorf("Expected: %s, Got: %s", ErrEmptyStack, err)
	}
}

func TestPushWithFewElements(t* testing.T) {
	tt := []struct {
		Name string
		Operations []interface{}
		Version Version
		Expected []int
		ExpectedErr error
	} {
		{
			Name: "Empty stack",
			Operations: []interface{}{},
			Version: -1,
			Expected: []int {},
			ExpectedErr: ErrNoVersionFound,
		},
		{
			Name: "Push 1 value",
			Operations: []interface{}{1},
			Version: 1,
			Expected: []int {1},
		},
		{
			Name: "Push 2 values print version 1",
			Operations: []interface{}{1, 2},
			Version: 1,
			Expected: []int {1},
		},
		{
			Name: "Push 2 values print version 2",
			Operations: []interface{}{1, 2},
			Version: 2,
			Expected: []int {1, 2},
		},
		{
			Name: "Push 10 values print version 5",
			Operations: []interface{}{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
			Version: 5,
			Expected: []int {1, 2, 3, 4, 5,},
		},
		{
			Name: "Push 2 values Pop 2 and version 4",
			Operations: []interface{}{1, 2, "POP", "POP"},
			Version: 4,
			Expected: []int {},
		},
		{
			Name: "Push 10 values Pop and get version 11",
			Operations: []interface{}{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, "POP"},
			Version: 11,
			Expected: []int {1, 2, 3, 4, 5, 6, 7, 8, 9},
		},
		{
			Name: "Push 10 values Pop 9 and get version 19",
			Operations: []interface{}{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, "POP", "POP", "POP", "POP", "POP", "POP", "POP" , "POP", "POP" },
			Version: 19,
			Expected: []int {1},
		},
	}
	for _, tc := range tt {
		t.Run(tc.Name, func(t *testing.T) {
			s := NewStack()
			for _, op := range tc.Operations {
				switch op.(type) {
				case int:
					s.Push(op.(int))
				case string:
					_, err := s.Pop()
					if err != nil{
						t.Errorf("Unxpected err:%s", err)
						return
					}
				}
			}
			stackElements, err := s.AsArray(tc.Version)
			if err != nil && tc.Version != -1{
				t.Errorf("Unxpected err:%s", err)
				return
			}
			if len(stackElements) != len(tc.Expected) {
				t.Errorf("Expected: %#v Got: %#v", tc.Expected, stackElements)
				return
			}
			for i := range tc.Expected {
				if tc.Expected[i] != stackElements[i] {
					t.Errorf("Values are not Equal at %d, Expected: %d, Got: %d", i, tc.Expected[i], stackElements[i])
				}
			}
		})

	}
}
