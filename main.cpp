#include "coordinate.h"
#include <iostream>
#include <ctime>
#include <stdiolib>


void add_coordinate(Coordinate *&list_end, float x, float y) 
{
    Coordinate *new_coord = new Coordinate{x, y, 0, nullptr, nullptr};

       if(list_end == nullptr) {
          new_coord->coord_id = 1;
          list_end = new_coord;
          new_coord->next = new_coord; 
          new_coord->previous = new_coord;
       } else {
          new_coord->coord_id = list_end->coord_id + 1;
          new_coord->previous = list_end;
          new_coord->next = list_end->next;
          list_end->next->previous = new_coord;
          list_end->next = new_coord;
          list_end = new_coord; 
       }
}


void forward_display(Coordinate *list_beginning) 
{
    Coordinate *current = list_beginning;

    if(!current) return;
    do {
 
       std::cout << "ID: " << current->coord_id << " | X: " << current->x << " | Y: " << current->y << std::endl;

        current = current->next;
    } while (current != list_beginning);
}


void backward_display(Coordinate *list_end) 
{
   Coordinate *current = list_end;
 
   if(!current) return;
   do {
        std::cout << "ID: " << current->coord_id << " | X: " << current->x << " | Y: " << current->y << std::endl;
     
   current = current->previous;
   } while (current != list_end);
}


void delete_coordinate(Coordinate *&list_beginning, int coord_id_to_delete) 
{
    if(!list_beginning) return;

    Coordinate *current = list_beginning;

    do {
        if(current->coord_id == coord_id_to_delete) 
	{
            if(current->next == current) 
	    {
                delete current;
                list_beginning = nullptr;
                return;
            }

            current->previous->next = current->next;
            current->next->previous = current->previous;
 
           if(current == list_beginning) 
	   {
                list_beginning = current->next; 
           }

           delete current;

           return;
        }

        current = current->next;
 
   	} while (current != list_beginning);
}


int list_length(Coordinate *list_beginning) 
{
    if(!list_beginning) return 0;
 
    int length = 0;

 	   Coordinate *current = list_beginning;
    	   do {
              length++;
              current = current->next;
    
    	   } while (current != list_beginning);
    
	return length;
}


void closest_to(Coordinate *list_beginning, float x, float y) 
{
    if(!list_beginning) return;

    float min_distance = std::numeric_limits<float>::max();
    Coordinate *closest = nullptr;

    Coordinate *current = list_beginning;
	    do {
        	float distance = std::sqrt(std::pow(current->x - x, 2) + std::pow(current->y - y, 2));
            if(distance < min_distance) 
	    {
            	min_distance = distance;
            	closest = current;
            }
      
	 	 current = current->next;
     
	    } while (current != list_beginning);

    if(closest) 
    {
        std::cout << "Closest Point: ID: " << closest->coord_id << " | X: " << closest->x << " | Y: " << closest->y << " | Distance: " << min_distance << std::endl;
    }
} 

int main(int argc, char *argv[]) 
{
    if(argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <number_of_coordinates>" << std::endl;
        return 1;
    }

    int num_coordinates = std::stoi(argv[1]);
    
	if(num_coordinates <= 0) 
	{
           std::cerr << "Please enter a positive integer." << std::endl;
           return 1;
    	}

    std::srand(std::time(0));
    Coordinate *list_beginning = nullptr;

    for(int i = 0; i < num_coordinates; i++) 
    {
        float x = static_cast<float>(std::rand() % 100); 
        float y = static_cast<float>(std::rand() % 100); 
     
	add_coordinate(list_beginning, x, y);
    }

    std::cout << "Coordinates in forward order:" << std::endl;
    forward_display(list_beginning);
    
    std::cout << "Coordinates in order backwards:" << std::endl;
    backward_display(list_beginning);

    std::cout << "Length of the entire list: " << list_length(list_beginning) << std::endl;

    
    delete_coordinate(list_beginning, 1);

    std::cout << "After Deleting Coordinate ID 1:" << std::endl;
    forward_display(list_beginning);

    
    closest_to(list_beginning, 50.0f, 50.0f);

   
    while(list_beginning) 
    {
        delete_coordinate(list_beginning, list_beginning->coord_id);
    }

    return 0;
}
