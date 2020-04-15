#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define _KEY_WORDEND "waiting for your expanding"
using namespace std;
typedef struct //�ʵĽṹ��Ԫ����ʽ�������ֱ����֣����ͣ����������ֵ��
{
	int typenum; //�����ֱ�
	char * type;
	char * word;
}WORD;
char input[255];
char token[255] = "";
int p_input; //ָ��
int p_token;
char ch;
char * rwtab[] = { "begin","if","then","while","do","end","int","main",
                        "else","float","double","return","cout",_KEY_WORDEND };

WORD * scanner();//ɨ��

int main()
{
	int over = 1;
	WORD* oneword = new WORD;

	//ʵ�ִ��ļ���ȡ�����
	cout << "read something from data.txt" << endl;
	FILE *fp;
	if((fp=freopen("D://data.txt","r",stdin))==NULL)
        {
                printf("Not found file!\n");
                return 0;
        }
        else
        {
                while ((scanf("%[^#]s", &input)) != EOF)
                {
                        p_input = 0;
                        printf("your words:\n%s\n", input);
                        while (over < 1000 && over != -1)
                        {
                                oneword = scanner();
                                if (oneword->typenum < 1000)
                                {
                                        if(oneword->typenum != 999)
                                                cout << oneword->word <<"\t"<< "<  "<< oneword->type <<"  >"<< endl;
                                }
                                over = oneword->typenum;
                        }
                        scanf("%[^#]s", input);
                }
        }
    return 0;
}

//�����뻺������ȡһ���ַ���ch��
char m_getch()
{
	ch = input[p_input];
	p_input++;
	return ch;
}

//ȥ���հ׷���
void getbc()
{
	while (ch == ' ' || ch == 10)
	{
		ch = input[p_input];
		p_input++;
	}
}

//ƴ�ӵ���
void concat()
{
	token[p_token] = ch;
	p_token++;
	token[p_token] = '\0';
}

//�ж��Ƿ���ĸ
int letter()
{
	if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z')
		return 1;
	else
		return 0;
}

//�ж��Ƿ�����
int digit()
{
	if (ch >= '0'&&ch <= '9')
		return 1;
	else
		return 0;
}

//�����ؼ��ֱ��
int reserve()
{
	int i = 0;
	while(strcmp(rwtab[i], _KEY_WORDEND))
	{
		if (!strcmp(rwtab[i], token))
			return i + 1;
		i++;
	}
	return 10;//������ǹؼ��֣��򷵻��ֱ���10
}

//����һ���ַ�
void retract()
{
	p_input--;
}

//�ʷ�ɨ�����
WORD * scanner()
{
	WORD * myword = new WORD;
	myword->typenum = 10;  //��ʼֵ
	myword->word = "";
	p_token = 0;   //���ʻ�����ָ��
	m_getch();
	getbc();//ȥ���հ�

	if (letter())//�ж϶�ȡ��������ĸ����ĸ
	{
	        //��int
		while (letter() || digit())
		{
			concat(); //����
			m_getch();
		}
		retract(); //����һ���ַ�
		myword->typenum = reserve();//�ж��Ƿ�Ϊ�ؼ��֣������ֱ���
		if(myword->typenum == 1){
            myword->type = "BEGIN";
		}
		else if(myword->typenum == 2){
            myword->type = "IF";
		}
		else if(myword->typenum == 3){
            myword->type = "THEN";
		}
		else if(myword->typenum == 4){
            myword->type = "WHILE";
		}
		else if(myword->typenum == 5){
            myword->type = "DO";
		}
		else if(myword->typenum == 6){
            myword->type = "END";
		}
		else if(myword->typenum == 7){
            myword->type = "INT";
		}
		else if(myword->typenum == 8){
            myword->type = "MAIN";
		}
		else if(myword->typenum == 9){
            myword->type = "ELSE";
		}
		else if(myword->typenum == 10){
            myword->type = "FLOAT";
		}
		else if(myword->typenum == 11){
            myword->type = "DOUBLE";
		}
		else if(myword->typenum == 12){
            myword->type = "RETURN";
		}
		else if(myword->typenum == 13){
            myword->type = "COUT";
		}
		else{
		myword->type = "IDN , num";
		}
		myword->word = token;
		return myword;
	}
	else if (digit())  //�ж϶�ȡ���ĵ������ַ�������
	{
		while (digit()) //����������������
		{
			concat();
			m_getch();
		}
		retract();
		//���ֵ����ֱ���ͳһΪ20�����������ֵΪ���ֱ���
		myword->typenum = 20;
		myword->word = token;
		myword->type = "CONST , " + token;
		return(myword);
	}
	else switch (ch)
	{
	case '=':
		m_getch();//���ַ�Ϊ=,�ٶ�ȡ��һ���ַ��ж�
		if (ch == '=')
		{
			myword->typenum = 39;
			myword->word = "==";
            myword->type = "INC";
			return(myword);
		}
		retract();//��ȡ�����¸��ַ�����=����Ҫ���ˣ�ֱ�����=
		myword->typenum = 21;
		myword->word = "=";
		myword->type = "INC";
		return(myword);
		break;
	case '+':
	    m_getch();//
		if (ch == '+')
		{
			myword->typenum = 90;
            myword->type = "INC";
			myword->word = "++";
			return(myword);
		}
		retract();//
		myword->typenum = 22;
		myword->word = "+";
		myword->type = "INC";
		return(myword);
		break;
	case '-':
		myword->typenum = 23;
		myword->word = "-";
		myword->type = "INC";
		return(myword);
		break;
        case '/'://��ȡ���÷���֮��Ҫ�ж���һ���ַ���ʲô���ţ��ж��Ƿ�Ϊע��
                m_getch();//���ַ�Ϊ/,�ٶ�ȡ��һ���ַ��ж�
		if (ch == '*') // ˵����ȡ������ע��
		{
		        m_getch();

			while(ch != '*')
                        {
                                m_getch();//ע��û����֮ǰһֱ��ȡע�ͣ��������
                                if(ch == '*')
                                {
                                        m_getch();
                                        if(ch == '/')//ע�ͽ���
                                        {
                                                myword->typenum = 999;
                                                myword->word = "ע��";
                                                return (myword);
                                                break;
                                        }
                                }

                        }

		}
                else
                {
                        retract();//��ȡ�����¸��ַ�����*��������ע�ͣ���Ҫ���ˣ�ֱ�����/

                        myword->typenum = 25;
                        myword->word = "/";
                        myword->type = "INC";
                        return (myword);
                        break;
                }
        case '*':
		myword->typenum = 24;
		myword->word = "*";
		myword->type = "INC";
		return(myword);
		break;
	case '(':
		myword->typenum = 26;
		myword->type = "SLP";
		myword->word = "(";
		return(myword);
		break;
	case ')':
		myword->typenum = 27;
		myword->type = "SRP";
		myword->word = ")";
		return(myword);
		break;
	case '[' :
		myword->typenum = 28;
		myword->type = "SLP";
		myword->word = "[";
		return(myword);
		break;
	case ']':
		myword->typenum = 29;
		myword->type = "SRP";
		myword->word = "]";
		return(myword);
		break;
	case '{':
		myword->typenum = 30;
		myword->type = "LP";
		myword->word = "{";
		return(myword);
		break;
	case '}':
		myword->typenum = 31;
		myword->type = "RP";
		myword->word = "}";
		return(myword);
		break;
	case ',':
		myword->typenum = 32;
		myword->type = "DEL"; //DEL���޷�
		myword->word = ",";
		return(myword);
		break;
	case ':':
		m_getch();
		if (ch == '=')
		{
			myword->typenum = 18;
			myword->word = ":=";
            myword->type = "SEMI";
			return(myword);
			break;
		}
		else
                {
                        retract();
                        myword->typenum = 33;
                        myword->word = ":";
                        myword->type = "SEMI";
                        return(myword);
                        break;
                }
        case ';':
                myword->typenum = 34;
                myword->type = "SEMI";
                myword->word = ";";
                return(myword);
                break;
	case '>':
		m_getch();
		if (ch == '=')
		{
			myword->typenum = 37;
			myword->word = ">=";
            myword->type = "SEMI";
			return(myword);
			break;
		}
		retract();
		myword->typenum = 35;
		myword->word = ">";
        myword->type = "SEMI";
		return(myword);
		break;
	case '<':
		m_getch();
		if (ch == '=')
		{
			myword->typenum = 38;
			myword->word = "<=";
            myword->type = "SEMI";
			return(myword);
			break;
		}
		else if(ch == '<')
                {
                        myword->typenum = 42;
			myword->word = "<<";
            myword->type = "SEMI";
			return(myword);
			break;
                }
                else
                {
                        retract();
                        myword->typenum = 36;
                        myword->word = "<";
                        myword->type = "SEMI";
                        return (myword);
                }
	case '!':
		m_getch();
		if (ch == '=')
		{
			myword->typenum = 40;
            myword->type = "NE";
			myword->word = "!=";
			return(myword);
			break;
		}
		retract();
		myword->typenum = -1;
		myword->word = "ERROR";
        myword->type = "ERROR";
		return(myword);
		break;
        case ' " ':
        myword->typenum = 41;
		myword->word = " \" ";
        myword->type = "SEMI";
		return(myword);
		break;
	case '\0':
		myword->typenum = 1000;
		myword->word = "OVER";
        myword->type = "SEMI";
		return(myword);
		break;
        case '#':
                myword->typenum = 0;
                myword->word = "#";
                myword->type = "SEMI";
                return (myword);
                break;
	default:
		myword->typenum = -1;
		myword->word = "ERROR";
        myword->type = "ERROR";
		return(myword);
		break;
	}
}

