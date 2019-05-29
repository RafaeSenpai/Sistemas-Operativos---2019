#include <sys/types.h>
typedef struct Pessoa *Person;



Person new_person(char* name, int age);

Person clone_person(Person p);

void destroy_person(int cod);

int person_age(int cod);

void person_change_age(int p, int age);



ssize_t readln(int fildes, void *buf, size_t nbyte);
void clearscr();
void printPerson(Person p);
void callNew_Person();
void callMenuOptions();
void menu(char opt);
void addPerson(Person p);
Person getPerson(int codPerson);
void call_clone_person();
void call_destroy_person();
void printAllPersons();
void call_person_age();
void call_person_change_age();
void call_get_person();