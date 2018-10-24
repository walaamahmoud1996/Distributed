struct SignUpargs{
	char* username;
	char* password;

};


program SIGNUP_PROG{
	version SIGNUP_VERS{

		int signup(SignUpargs)=1;
	}=1;

}=0x2345111;
