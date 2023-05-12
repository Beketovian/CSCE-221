#include <iostream>
#include "StemAndLeaf.h"

int StemAndLeaf::getLeafUnit() const { 
  return leafUnit;
}


void StemAndLeaf::setLeafUnit(int leafUnit) {
  this->leafUnit = leafUnit;
}

int StemAndLeaf::getStemUnit() const { 
  return stemUnit;
}

void StemAndLeaf::setStemUnit(int stemUnit) {
  this->stemUnit = stemUnit;
} 

StemAndLeaf::StemAndLeaf() {
  head = nullptr;
  tail = nullptr;

}

StemAndLeaf::~StemAndLeaf() {
  Stem* curr = head;
  while(curr != nullptr)
  {
    Stem* temp = curr->next;
    delete curr;
    curr = temp;
  }
}

//add
void StemAndLeaf::addTerm(int term) {
	//for easier use cuz i had to rewrite function to fix bug
    int stemValue = term / stemUnit * stemUnit / 10; // /10
    int leafValue = term % stemUnit / leafUnit * leafUnit;

    //if empty then create and set freq to 0. Set head and tail equal cuz only one element
    if(head == nullptr)
    {
        head = new Stem();
        head->value = stemValue;
        head->frequency = 0;
        head->next = nullptr;
        head->insert(leafValue);
        tail = head;
    }
    //check if term is same as tail
    else if(stemValue == tail->value)
    {
        tail->insert(leafValue);
    }
	//not empty or tail then make or find
    else
    {
        //search for existing stem with stemValue instead of creating new empty stem by traversing
        Stem* curr = head;
        Stem* prev = nullptr;
        while(curr != nullptr && curr->value < stemValue)
        {
            prev = curr;
            curr = curr->next;
        }
		//if found existing then insert
        if(curr != nullptr && curr->value == stemValue)
		{
            curr->insert(leafValue);
        }
		//if not found then make new
		else
		{
            //create new stem and insert
            Stem* newStem = new Stem();
            newStem->value = stemValue;
            newStem->frequency = 0;
            newStem->next = curr;
            newStem->insert(leafValue);
			//if newStem now head, set as it
            if(curr == head)
            {
                head = newStem;
            }
			//else set previous next to newStem
            else
            {
                prev->next = newStem;
            }
        }
    }

	/*
	//if empty then create and set freq to 0. Set head and tail equal as there is only one element
	if(head == nullptr)
	{
		head = new Stem();
		head->value = term / stemUnit * stemUnit;
		head->frequency = 0;
		head->next = nullptr;
		//std::cout<<"addterminsert: " << term << " - " << term % stemUnit / leafUnit * leafUnit<< std::endl;
		head->insert(term % stemUnit / leafUnit * leafUnit);
		tail = head;
	}
	//check for if term is same as tail
	else if(term / stemUnit * stemUnit == tail->value)
	{
		//std::cout<<"addterminsert: " << term << " - " << term % stemUnit / leafUnit * leafUnit<< std::endl;;
		tail->insert(term % stemUnit / leafUnit * leafUnit);
	}
	//if not empty or tail, put in
	else
	{
		//loop through and find stem that input belongs to
		Stem* curr = head;
		while(curr->value < term / stemUnit * stemUnit)
		{
			if(curr->next == nullptr)
			{
				curr->next = new Stem();
				curr->next->value = curr->value + stemUnit;
				curr->next->frequency = 0;
				curr->next->next = nullptr;
				tail = curr->next;
			}
			curr = curr->next;
		}
		//if found, insert
		if(curr->value == term / stemUnit * stemUnit)
		{
			//std::cout<<"addterminsert: " << term << " - " << term % stemUnit / leafUnit * leafUnit<< std::endl;
			curr->insert(term % stemUnit / leafUnit * leafUnit);
		}
		//if not found, create a new stem and insert
		else
		{
			Stem* newStem = new Stem();
			newStem->value = term / stemUnit * stemUnit;
			newStem->frequency = 0;
			newStem->next = curr;
			//std::cout<<"addterminsert: " << term << " - " << term % stemUnit / leafUnit * leafUnit << std::endl;
			newStem->insert(term % stemUnit / leafUnit * leafUnit);
			//if curr is at head, head = newStem. Otherwise, traverse until next is equal to curr and set next to newStem
			if(curr == head)
			{
				head = newStem;
			}
			else
			{
				Stem* temp = head;
				while(temp->next != curr)
				{
					temp = temp->next;
				}
				temp->next = newStem;
			}
				//std::cout << newStem->value << std:: endl;
		}
	}
	*/
	//std::cout << "SU: " << stemUnit << std::endl;
}


bool StemAndLeaf::removeTerm(int term) {
	// std::cout << "TEST: " << term % stemUnit / leafUnit * leafUnit << std::endl;
	// std::cout << "TEST TRAVERSAL: " << term / stemUnit * stemUnit << std::endl;
    //if list is empty return false cuz nothing was removed
    if(head == nullptr)
	{
        return false;
    }
    //if term we want to remove is the head
    else if(term / stemUnit * stemUnit / 10 == head->value)
	{
        //try remove term from head check rem gonna be a check for if we removed smt
        bool checkrem = head->remove(term % stemUnit / leafUnit * leafUnit);
        //if head empty, head = head->next
        if(head->frequency == 0)
		{
            Stem* temp = head;
            head = head->next;
            delete temp;
        }
        //return the removal result
        return checkrem;
    }
    //else we traverse until curr val is term
    else
	{
        Stem* curr = head;
        while(curr->value < term / stemUnit * stemUnit / 10)
		{
            if(curr->next == nullptr)
			{
                return false;
            }
            curr = curr->next;
        }
        //if found try remove. checkrem same as above
        if(curr->value == term / stemUnit * stemUnit / 10)
		{
            bool checkrem = curr->remove(term % stemUnit / leafUnit * leafUnit);
            //if the stem empty set prev stem next pointer to next
            if(curr->frequency == 0)
			{
                Stem* temp = head;
                while(temp->next != curr)
				{
                    temp = temp->next;
                }
                temp->next = curr->next;
                if(curr == tail)
				{
                    tail = temp;
                }
                delete curr;
            }
            //return if removed
            return checkrem;
        }
        return false;
    }
}


// Don't modify
std::ostream &operator << (std::ostream &out, const StemAndLeaf &x) {
	// needs to go through the StemAndLeaf, one stem, then all leaves, then back to the next stem and it's leaves, and continue
    Stem * CURSTEM_ptr = x.head;
    while ( CURSTEM_ptr != nullptr )
    {
      out << *CURSTEM_ptr; 
      CURSTEM_ptr = CURSTEM_ptr -> next;
    }
    
	return out;
}

