# touristbooking
this code is based on single linked list
the structure of  this code is
Objective:
To implement a tourist booking system for a trip to Bali, Indonesia, where each tourist is added to a TRIP list or a WAITLIST, depending on the availability of slots. The system uses singly linked lists and supports booking, cancellation, and data display functionalities.
Key Data Structures:
    struct details: Represents a node in the linked list with the following fields:
        first_name: Tourist’s first name.
        last_name: Tourist’s last name.
        booking_date: Unique integer representing the date of booking .
        next: Pointer to the next node.
