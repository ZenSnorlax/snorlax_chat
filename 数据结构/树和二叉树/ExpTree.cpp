#include<iostream>
#include<ctype.h>
#define MAXSIZE 100
using namespace std;
char ch;
template <class T>
class Stack{
	private:
	T *top;
	T *base;
	public:
	void Init();//初始化栈
	void Push(T const &);//入栈
	T Pop(); //出栈
	T GetTop(); //取栈顶 
};
template <class T>
void Stack<T>::Init(){
	base = new T[MAXSIZE];
	top = base;
}
template <class T>
void Stack<T>::Push(T const &e){
	if(top - base == MAXSIZE) exit(1);
	*top++ = e;
}
template <class T>
T Stack<T>::Pop(){
	if(top == base) exit(1);
	return *--top;	
}
template <class T>
T Stack<T>::GetTop(){
	if(top == base) exit(1);
	return *top;
}
//二叉树定义
struct TreeNode{
	TreeNode *l, *r;
	char date;
};
void CreateExpTree(TreeNode *p, TreeNode *lchild, TreeNode *rchild, char op){
		p->l = lchild;
		p->r = rchild;
		p->date = op;
}
//跳过无效字符
void next(){
	cin>>ch;
	if(ch == ' '||ch == '\t'||ch == '\n')
	next();
}
char Precede(char l, char r){
	return '#';		
}
//构造表达树 
void ExpTree(){
	Stack<char> OPTR; //运算符
	Stack<TreeNode> EXPT; //根节点
	OPTR.Init();
	EXPT.Init();
	OPTR.Push('#');
	next();
	while(ch != '#' || OPTR.GetTop() != '#'){
	if(isdigit(ch)){
			TreeNode * t = new TreeNode;
			CreateExpTree(t, NULL, NULL, ch);
			EXPT.Push(*t);
			next();
		}
		else {
			TreeNode *t1 = new TreeNode;
			TreeNode *lchild = new TreeNode;
			TreeNode *rchild = new TreeNode;
			TreeNode *t2 = new TreeNode;
			char theta;
			switch(Precede(OPTR.GetTop(), ch)){
				case '<':
				CreateExpTree(t1, NULL, NULL, ch);
			 	next();
				break;
				case '>':
				theta = OPTR.Pop(); 
				*lchild = EXPT.Pop();
				*rchild = EXPT.Pop();
				CreateExpTree(t2, lchild, rchild, theta);
				EXPT.Push(*t2);
				break;
				case '=':
				OPTR.Pop();
				next();
				break;
			}

		}

	}

}

