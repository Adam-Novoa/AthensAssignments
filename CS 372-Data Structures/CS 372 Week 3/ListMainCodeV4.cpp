
int main()
  {
  	List a,b;  int endit;

	for (int i=1;i<=20;i++)
	   a.insertAfter(i);
	cout << "List a : " << endl;
    cout << "  "  << a << endl;
	cout << "Number of elements in a - " << a.size() << endl;

	for (int i=1;i<=20;i++)
	   b.insertBefore(i);
	cout << "List b : " << endl;
    cout << "  "  <<  b << endl;
	cout << "Number of elements in b - " << b.size() << endl;

	if ( a == b )
	    cout << "List a & b are equal" << endl;
	  else
	    cout << "List a & b are Not equal" << endl;

	a.front();
	b.front();
	cout << "First elmenet in list a & b: " << a.getElement() << ", "
				       << b.getElement() << endl;
	for ( int i = 0; i < a.size(); a.next(),i++);
	for ( int i = 0; i < b.size(); b.next(),i++);
	cout << "Last elmenet in list a & b: " << a.getElement() << ", "
				     << b.getElement() << endl;
	cout << endl << endl << " Start of new stuff" << endl;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	a.front();
	b.front();
	endit = a.size()/2;
	for ( int i = 1; i<endit; i++)
	{  a.next();
	   b.next();
	}

	cout << "New position in Obj 'a' position = " << a.size()/2 << endl;

	for ( int i=1; i<8; i++)
	{
	   a.erase();
	   b.replace(i);
	}

	cout << "Modified Object 'a' " << endl;
    cout << "List a: " << a << endl;

	List c(b);
	cout << "Copy Constructor c(b)" << endl;
    cout << "List b : " << b << endl;
    cout << "List c : " << c << endl;

	if ( c == b )
	    cout << "List c & b are equal" << endl;
	  else
	    cout << "List c & b are Not equal" << endl;


	List e;
	e = c;
	cout << "Object 'c' assigned to Object 'e':" << endl;
    cout << "List c : " << c << endl;
    cout << "List e : " << e << endl;

    List d;
	d=a;
	d.front();
	endit = d.size()/2;
	for (int i=1; i<=endit; i++)
	{
		d.next();
		d.erase();
	}
	cout << "Results after some erases: Object d  " << endl;
    cout << "List d : " << d << endl;

	d.front();
	endit = d.size();
	for ( int i = 1; i < endit; d.next(), i++)
	{
		d.insertBefore(d.getElement()*2);
		d.next();
	}
	cout << "Results after some Replaces on d " << endl;
    cout << "List d : " << d << endl;

	a.front();
	endit = a.size();
	for ( int i = 1; i < endit; a.next(), i++)
	{
		a.insertBefore(a.getPos()+a.getElement());
		a.next();
		a.erase();
	}
	cout << "Results after some weird stuff on list a" << endl;
    cout << "List a : " << a << endl;

    List alist(b);
    alist.clear();
    for (int i=1;i<=10;i++)
	   alist.insertAfter(i);
	alist.front();
	cout << "New List alist with positions above: " << endl;
    for (int i=1;i<=10;i++) {
		cout << setw(5) << alist.getPos();
		alist.next();
	}
	cout << endl;
	alist.front();
	for (int i=1;i<=10;i++) {
		cout << setw(5) << alist.getElement();
		alist.next();
	}
	cout << endl;
	
    alist.reverse();
    cout << "Reverse New List alist : " << endl;
    cout << "  "  << alist << endl;

    List newa;
    for (int i=1;i<=20;i++)
	   newa.insertAfter(i*3);
    cout << "List alist and newa before swap " << endl;
    cout << " " << alist << endl;
    cout << " " << newa << endl;
    alist.swap(newa);
    cout << "List alist and newa after swap " << endl;
    cout << " " << alist << endl;
    cout << " " << newa << endl;


	cout << endl << "  check out boundary conditions" << endl;
	List sq;
	cout << "number of elements in empty sq list = " << sq.size() << endl;
	sq.front();
	sq.erase();
	cout << "empty sq values " << sq << endl;
	sq.insertBefore(999);
	cout << "sq values " << sq << endl;
	sq.next(); sq.next();
	cout << "sq.getElement() = " << sq.getElement() << endl;
	cout << "sq values " << sq << endl;
	system("pause");   //This statement not needed in code blocks, just VS.
	return 0;
  }
