#include <cstdlib>
#include <cstring>

class N
{
	public:
		N::N(int value) : value(value) {}

		int operator+(const N &rhs) { return this->value + rhs.value; }
		void setAnnotation(char *annotation) { strcpy(this->annotation, annotation); }

		char annotation[100];
		int value;
};

void main(int argc, char **argv)
{
	if (argc < 2)
	{
		exit(1);
	}

	N *obj1 = new N(5);
	N *obj2 = new N(6);

	obj1->setAnnotation(argv[1]);
	*obj2 + *obj1;
	return;
}