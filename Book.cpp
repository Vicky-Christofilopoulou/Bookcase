#include <iostream>
#include <string>
using namespace std;

class Book
{
    public:
        Book(string t, string a, string num);               //Constructor
        ~Book(){};                                          //Destructor
        void get_book();
		string getTitle(){return title;}
		string getAuthor(){return author;}
        string getIsbn(){return ISBN;}
    private:
        string title;
		string author;
		string ISBN;
};

class Shelf
{
	public:
	    Shelf(int N);                                        //Constructor
	    ~Shelf();                                            //Destructor
	    bool place_book(Book *book);
	    bool take_book();
	    int get_numbooks();                                //Number of books in the Shelf
	    void print() const;
	private:
	    int num_books;                                      //Counter for the number of books
	    Book **Array;                                       //Keeps the books in each Shelf
	    int Nmax;
};

class Cupboard 		                    
{
	public:
	    Cupboard(int N);                                 //Constructor
	    ~Cupboard();                                    //Destructor
	    bool place_book(int in_shelf,Book *book);
	    bool take_book(int in_shelf);
	    int get_numbooks(int in_shelf);                 //Number of books 
	    void print() const;
	private:
	    Shelf CupShelfTop;
        Shelf CupShelfBot;
};

class Base
{
    public:
	    Base(){cout<<"Constructing Base..."<< endl;}            //Constructor
	    ~Base(){cout<<"Destructing Base..."<< endl;}            //Destructor
};

class Bookcase 
{
    public:
        Bookcase(int N);                //Constructor
        ~Bookcase();                     //Destructor
        bool place_book(int in_place, Book *book);      //Adds a book
        bool take_book(int in_place);
        void print() const;
    private:
        Base BookBase;                  //Bookcase has 1 base
        Cupboard BookCupb;              //Bookcase has 1 cupboard
        Shelf BookShelfTop;             //Bookcase has 3 Bookshelfs
        Shelf BookShelfMid; 
        Shelf BookShelfBot; 
        int libBooks;                   //number of book of the bookcase
        int Nmax;
};

void Text(void)
{
	cout<< "1 for the top bookcase Shelf."<< endl;
	cout<< "2 for the middle bookcase Shelf."<< endl;
	cout<< "3 for the bottom bookcase Shelf."<< endl;
	cout<< "4 for the top Shelf of the cupboard."<<endl;
	cout<< "5 for the bottom Shelf of the cupboard."<<endl<<endl;
}

int main(int argc, char *argv[])
{
    int Nmax;           //Max number of book in each self 
	int L;              //number of book
    int K1;             //number of placements of the books in the bookcase
    int K2;             //Number of removals of the books out of the bookcase
    int i;
    string title, author, ISBN;
    
    if (argc !=5)
    {
        cout<<"Wrong number of arguments. You must type 4 arguments."<<endl;
        exit(1);
    }
    Nmax= atoi(argv[1]);
    L=atoi(argv[2]);
    K1=atoi(argv[3]);
    K2=atoi(argv[4]);
    
    Bookcase b(Nmax);                            //Creating the Bookcase
    Book **tempBooks = new Book*[L];     	    // Creating an array to keep the books before I place them

    if(K1>L)	//if the books I have are less that the placements
		K1=L;               
    for (i=0; i<L; i++)  // I have l books to create
    {
        cout<<"Enter Title."<< endl;
    	getline(cin,title);                 //getline - just like cin but includes white spaces
    	cout<<"Enter Author."<< endl;
    	getline(cin,author);
    	cout<<"Enter ISBN."<< endl;
    	getline(cin,ISBN); 
        tempBooks[i]= new Book(title, author, ISBN);
        cout << "I just created a Book with value: " << title << ' ' << author << ' ' << ISBN << endl;
    }
    for (i=0; i< K1; i++)
    {
        cout<< endl <<"Where do you want to add the book?" <<endl<< endl;;
        Text();
    	int place;
    	cin>>place;
    	if (place < 0 || place > 5)    //Invalid number
    	{
    	    cout<<"Wrong number."<<endl;
    	    exit(1);
    	}
        b.place_book(place,tempBooks[i]);
    }
    for (i=0; i<K2; i++)
    {
        cout<< endl <<"From where do you want to remove the book?"<< endl<< endl;;
        Text();
    	int place;
    	cin>>place;
    	if (place < 0 || place > 5)    //Invalid number
    	{
    	    cout<<"Wrong number."<<endl;
    	    exit(1);
    	}
        b.take_book(place);
    }
    b.print();
    for (i = 0 ; i<L; i++)
        delete tempBooks[i];
    delete[]  tempBooks;
    return 0;
}

//Functions for Book
Book::Book(string t = "\0", string a = "\0", string num = "\0"):title(t),author(a), ISBN(num){}

void Book::get_book()
{
   cout << title << ' ' << author << ' ' << ISBN << endl;
}


//Functions for Shelf
Shelf::Shelf(int N): Nmax(N)
{
	num_books=0;
    Array = new Book *[Nmax];                   //Creating an Array of pointer to books
    if (!Array)
    {
        cout<<"Error allocating memory!"<< endl;
        exit(1);
    }
    cout<<"Constructing Shelf..."<< endl;
}

Shelf::~Shelf()
{
    cout<<"Destructing Shelf..."<< endl;
    delete[] Array;
}

void Shelf::print() const
{
	if (num_books == 0)
    {
    	cout<<"The self is now empty."<< endl;
	}
	else 
	{
		for (int i=0; i < num_books; i++)
		{
			Array[i]->get_book();	
		}  
    }
}

bool Shelf::place_book(Book *book)
{
    Array[num_books]= book;
    Array[num_books]->get_book();
    num_books=num_books +1;	
    return true;
}

bool Shelf::take_book()
{
    Array[num_books]=NULL;	//(ΝULL= δεν υπάρχει βιβλίο πια)
    num_books=num_books -1;
    if (num_books == 0)
    { 
        cout<<"The Shelf is empty."<< endl;
    }
    else
    {
        cout << "The Shelf now contains:"<< endl;
        print();
    }
    return true;
}

int Shelf::get_numbooks()
{
    return num_books;
}

//Functions for Cupboard
Cupboard::Cupboard(int N) : CupShelfTop(N), CupShelfBot(N)
{
    cout<<"Constructing Cupboard..."<< endl;
}

Cupboard::~Cupboard()
{
    cout<<"Destructing Cupboard..."<< endl;
}

bool Cupboard::place_book(int in_shelf, Book *book)
{
    if (in_shelf == 1)
    {
        return CupShelfTop.place_book(book);
    }
    else
    {
        return CupShelfBot.place_book(book);
    }
}

void Cupboard::print() const
{
    cout<<endl<<"Top Shelf of the Cupboard."<<endl;
	CupShelfTop.print();
	cout<<endl<<"Bottom Shelf of the Cupboard."<<endl;
	CupShelfBot.print();
}

bool Cupboard::take_book(int in_shelf)
{
    if (in_shelf == 1)
    {
        cout<< "Top Shelf:"<< endl;
        CupShelfTop.take_book();
        cout <<"Bottom Shelf:"<< endl;   //print books of the bottom Shelf
        CupShelfBot.print();
    }
    else
    {
        cout<< "Top Shelf:"<< endl;
        CupShelfTop.print();
        cout <<"Bottom Shelf:"<< endl;
        CupShelfBot.take_book();  
    }
    return true;
}

int Cupboard::get_numbooks(int in_shelf)
{
    if (in_shelf == 1)
    {
        return CupShelfTop.get_numbooks();
    }
    else
    {
       return CupShelfBot.get_numbooks();
    }
}

//Functions for Bookcase
Bookcase :: Bookcase(int N):BookCupb(N), BookShelfTop(N), BookShelfMid(N), BookShelfBot(N)
{
    Nmax=N;
    libBooks=0;
    cout<<"Constructing Bookcase..."<< endl;
}

Bookcase::~Bookcase()
{
    cout<<"Destructing Bookcase..."<< endl;
}

bool Bookcase::place_book(int in_place, Book *book)
{
    if (in_place == 1) 
    {
        if (BookShelfTop.get_numbooks() < Nmax)  //top bookcase Shelf & I can add a book
        {
            BookShelfTop.place_book(book);
            libBooks = libBooks+1;
            cout<<"Placing the book at the top shelf of the bookcase."<<endl;
            return true;
        }
        else
        {
            cout<<"Sorry the top shelf of the bookcase is already full."<<endl;
            return false;
        }
    }
    else if (in_place == 2)
    {
        if (BookShelfMid.get_numbooks() < Nmax)                  //middle bookcase Shelf & I can add a book
        {
            BookShelfMid.place_book(book);
            libBooks = libBooks+1;
            cout<<"Placing the book at the middle shelf of the bookcase."<<endl;
            return true;
        }
        else
        {
            cout<<"Sorry the middle shelf of the bookcase is already full."<<endl;
            return false;
        }
    }
    else if (in_place == 3)
    {
        if (BookShelfBot.get_numbooks() < Nmax)  //bottom bookcase Shelf & I can add a book
        {
            BookShelfBot.place_book(book);
            libBooks = libBooks+1;
            cout<<"Placing the book at the bottom shelf of the bookcase."<<endl;
            return true;
        }
        else
        {
            cout<<"Sorry the bottom shelf of the bookcase is already full."<<endl;
            return false;
        }
    }
    else if (in_place == 4)
    {
        if (BookCupb.get_numbooks(1) < Nmax)                //top Shelf of the cupboard & I can add a book
        {
            BookCupb.place_book(1,book);
            libBooks = libBooks+1;
            cout<<"Placing the book at the top shelf of the cupboard."<<endl;
            return true;
        }
        else
        {
            cout<<"Sorry the top shelf of the cupboard is already full."<<endl;
            return false;
        }
    }
    else 
    {
        if (BookCupb.get_numbooks(2) < Nmax)                //bottom Shelf of the cupboard & I can add a book
        {
            BookCupb.place_book(2,book);
            libBooks = libBooks+1;
            cout<<"Placing the book at the bottom shelf of the cupboard."<<endl;
            return true;
        }
        else
        {
            cout<<"Sorry the bottom shelf of the cupboard is already full."<<endl;
            return false;
        }
    }
}

bool Bookcase::take_book(int in_place)
{
    if (in_place == 1) 
    {
        if (BookShelfTop.get_numbooks() > 0)  //top bookcase Shelf & I can remove a book
        {
            BookShelfTop.take_book();
            libBooks = libBooks -1;
            cout<<"Removing a book from the top shelf of the bookcase."<<endl;
            return true;
        }
        else
        {
            cout<<"Sorry the top shelf of the bookcase is empty."<<endl;
            return false;
        }
    }
    else if (in_place == 2)
    {
        if (BookShelfMid.get_numbooks() > 0)                    //middle bookcase Shelf & I can remove a book
        {
            BookShelfMid.take_book();
            libBooks = libBooks-1;
            cout<<"Removing a book from the middle shelf of the bookcase."<<endl;
            return true;
        }
        else
        {
            cout<<"Sorry the middle shelf of the bookcase is empty."<<endl;
            return false;
        }
    }
    else if (in_place == 3)
    {
        if (BookShelfBot.get_numbooks() > 0)  //bottom bookcase Shelf & I can remove a book
        {
            BookShelfBot.take_book();
            libBooks = libBooks-1;
            cout<<"Removing a book from the bottom shelf of the bookcase."<<endl;
            return true;
        }
        else
        {
            cout<<"Sorry the bottom shelf of the bookcase is empty."<<endl;
            return false;
        }
    }
    else if (in_place == 4)
    {
        if (BookCupb.get_numbooks(2) > 0)                //top Shelf of the cupboard & I can remove a book
        {
            BookCupb.take_book(1);
            libBooks = libBooks-1;
            cout<<"Removing a book from the top shelf of the cupboard."<<endl;
            return true;
        }
        else
        {
            cout<<"Sorry the top shelf of the cupboard is empty."<<endl;
            return false;
        }
    }
    else 
    {
        if (BookCupb.get_numbooks(2) > 0)                //bottom Shelf of the cupboard & I can remove a book
        {
            BookCupb.take_book(0);
            libBooks = libBooks-1;
            cout<<"Removing a book from the bottom shelf of the cupboard."<<endl;
            return true;
        }
        else
        {
            cout<<"Sorry the bottom shelf of the cupboard is empty."<<endl;
            return false;
        }
    }
}

void Bookcase::print() const
{
    cout<<endl<<"The cupboard contains:"<<endl;
    BookCupb.print();
    cout<< endl<<"Shelf of the Bookcase:"<<endl;
    cout<< endl<<"Bottom Shelf:"<<endl;
    BookShelfBot.print();
    cout<< endl<<"Middle Shelf:"<<endl;
    BookShelfMid.print();
    cout<< endl<<"Top Shelf:"<<endl;
    BookShelfTop.print();
    cout<<endl;
}