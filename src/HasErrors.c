// This file is a test bed for compilation errors to test EX 1-24 with
//! It is not intended to compile succesfully!
#if 0

int
main()
{
    // Checking for unbalanced paranthesis: 

    //* These should be ignored
    // Comment trap ( )
    // Comment trap ( ))))))
    #define TestingParenthesis "( ( (( ) )" 

    //*  These  should actually trigger an error
    if( ()
    {
        {
            {}}}}}

        }
        doThing();
    }

}
#endif