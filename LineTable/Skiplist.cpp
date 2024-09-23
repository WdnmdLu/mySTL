#include<set>
#include<ctime>
#include<cstdio>
#include<random>
template<typename T> 
class skiplist
{
	private:
	static constexpr int MAX_LEVEL = 16;
	static constexpr double P = 0.6;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<> dis;
	struct node
	{
		T data;
		node *next[MAX_LEVEL+1];// 存储第i层的后继节点
		node()
		{// 初始化时该节点的每层后继节点都为null
			for(int i=1;i<=MAX_LEVEL;i++)
				next[i] = NULL;
		}
	};
	node *head;
	public:
	skiplist()
	{
		head = new node;
		gen = std::mt19937(rd());
		dis = std::uniform_real_distribution<> (0,1);
	}//生成随机层数
	int randomLevel()
	{
		int ret = 1;
		while(ret<MAX_LEVEL && dis(gen)<P)
			ret++;
		return ret;
	}
	void insert(T x)
	{
		node *tmp = new node;
		tmp->data = x;
		node *pre[MAX_LEVEL+1];//记录一下要插入的新节点的前驱节点
		node *now = head;
		int level = randomLevel();//获取新插入节点所应位于的层数
		for(int i=MAX_LEVEL;i>=1;i--)
		{
			while(now->next[i] != NULL && now->next[i]->data<x) now = now->next[i];
			pre[i] = now;
		}
		
		for(int i=level;i>=1;i--)
		{
			tmp->next[i] = pre[i]->next[i];
			pre[i]->next[i] = tmp;
		}
	}
	bool remove(T x)
	{
		node *pre[MAX_LEVEL+1];
		node *now = head;
		for(int i=MAX_LEVEL;i>=1;i--)
		{
			while(now->next[i] != NULL && now->next[i]->data<x) now = now->next[i];
			pre[i] = now;
		}
		if(now->next[1] == NULL) return false;
		if(now->next[1]->data != x) return false;

		node *del = now->next[1];
		for(int i=MAX_LEVEL;i>=1;i--)
    	{
			if(pre[i]->next[i] != NULL && pre[i]->next[i] == del) pre[i]->next[i] = pre[i]->next[i]->next[i];
    	}
		delete del;
		
		return true;
	}
	bool find(T x)
	{
		node *now = head;
		for(int i=MAX_LEVEL;i>=1;i--)
			while(now->next[i] != NULL && now->next[i]->data<x) now = now->next[i];
		if(now->next[1] == NULL) return false;
		if(now->next[1]->data != x) return false;
		return true;
	}
	void print()
	{
		node *now = head->next[1];
		while(now != NULL)
		{
			printf("%d ",now->data);
			now = now->next[1];
		}
		printf("\n");
	}
};
int main()
{
	for(int i=1;i<=10;i++)
	{
		std::set<int> S; 
		skiplist<int> L;
		double clk1 = clock();
		for(int i=100000;i>=1;i--)
			L.insert(i);
		double clk2 = clock();
		for(int i=100000;i>=1;i--)
			S.insert(i);
		double clk3 = clock();
		printf("skiplist:%lf,set:%lf\n",clk2-clk1,clk3-clk2);
	}
	return 0;
}
