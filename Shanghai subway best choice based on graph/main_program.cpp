#include<stdio.h>
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#include<iostream>
#include<stack>
#include"graph.h"
#define Maxsize 600
using namespace std;
int sta_pos(vector<string> &sta_name,string name)//用于返回地铁站对应的顶点名
{
	vector<string>::iterator iter = find(sta_name.begin(), sta_name.end(), name);
	if (iter == sta_name.end())
		return -1;
	else
		return (int)distance(sta_name.begin(), iter);
}
int get_VertexNode(Graph <int>& map, vector<string> &sta_name, string name)//用于获取地铁站名对应的顶点名，若顶点表中未没有该顶点则新加顶点
{
    int pos = sta_pos(sta_name, name);
    if (pos != -1)
        return pos;
    else
    {
        map.InsertVertex(sta_name.size());
        sta_name.push_back(name);
        return sta_name.size() - 1;
    }
}
void ShortestPath(Graph <int>& G, int v, int* Dist, int* Pre, int* S)//使用Dijkstra算法获取最短路径
{
    int i, j, k, n = G.VerticesNumber();
    int Min, w;
    for (i = 0; i < n; i++) 
    {
        Dist[i] = G.GetWeight(v, i);  S[i] = 0;
        if (Dist[i]!=0)  
            Pre[i] = v;  
        else  
            Pre[i] = -1;
    }
    S[v] = 1;
    Pre[v] = -1; 
    for (i = 0; i < n - 1; i++) 
    {  
        Min = 60000;
        k = -1;
        for (j = 0; j < n; j++) 
            if (S[j] == 0 &&Dist[j]!=0&& Dist[j] < Min) 
            { 
                Min = Dist[j]; 
                k = j;
            }
        if (k == -1)
            break;
        S[k] = 1; 
        for (j = G.GetFirstNeighbor(k); j != -1; j = G.GetNextNeighbor(k, j))
        { 
            w = G.GetWeight(k, j);
            if (S[j] == 0 && w!=0 && (Dist[k] + w < Dist[j]||Dist[j]==0))
            {
                Dist[j] = Dist[k] + w; 
                Pre[j] = k;
            }
        }
    }
}
//初始化函数，将站点信息导入表中，同时标识站点是几号线
bool initialize(int* line,int line_seq,vector<string>line_name,vector<int>line_time,Graph<int>&map, vector<string> &sta_name)
{
    int n = line_name.size();
    int i;
    int v1=-1, v2=-1;
    for (i = 0; i < n-1; i++)
    {

        v1=get_VertexNode(map, sta_name, line_name[i]);
        v2 = get_VertexNode(map, sta_name, line_name[i + 1]);
        map.InsertEdge(v1, v2,line_seq, line_time[i]);
        map.InsertEdge(v2, v1, line_seq,line_time[i]);
        if (line[v1] == 0)
            line[v1] = line_seq;
        else
            line[v1] = -1;
    }
    if (line[v2] == 0)
        line[v2] = line_seq;
    else
        line[v2] = -1;
    return true;
}
void output(Graph<int> &map,vector<string> sta_name,string destination,int*pre,int d1,int d2,int*line)
{
    stack<int> path;
    path.push(d2);
    int i = d2;
    while(pre[i]!=-1)
    {
        path.push(pre[i]);
        i = pre[i];
    }
    int current_line=0;
    while (!path.empty())
    {
        i = path.top();
        path.pop();
        if (i == d2)
        {
            cout << sta_name[i];
            break;
        }
        if (i == d1)
        {
            int j = path.top();
            cout << sta_name[i];
            current_line = map.GetLine(i, j);
            printf("-");
            printf("line %d-", current_line);
        }
        if (line[i] == -1)
        {
            int j = path.top();
            if (map.GetLine(i,j)!=current_line)
            {
                current_line = map.GetLine(i, j);
                cout << sta_name[i];
                printf("-");
                printf("line %d-", current_line);
            }
        }
    }
    printf("\b");
    printf("\n");
    return;
}
int main()
{
	vector<string> sta_name;//用于存储站点的名字，每个元素的下标就是该站点在图中的顶点名
	Graph<int> map(Maxsize);
    int line[Maxsize] = {0};//用于存储各站点是哪一条线上的，-1表示是换乘站
    vector<string> line1_name = { "莘庄",	"外环路",	"莲花路",	"锦江乐园",	"上海南站",	"漕宝路",	"上海体育馆",	"徐家汇",	"衡山路",	"常熟路",	"陕西南路",	"黄陂南路",	"人民广场",	"新闸路",	"汉中路",	"上海火车站",	"中山北路",	"延长路",	"上海马戏城",	"汶水路",	"彭浦新村",	"共康路",	"通河新村",	"呼兰路",	"共富新村",	"宝安公路",	"友谊西路",	"富锦路"};
    vector<int> line1_time = { 2,	2,	3,	3,	3,	3,	2,	2,	2,	2,	2,	3,	2,	2,	3,	2,	3,	2,	2,	3,	3,	2,	2,	3,	3,	2,	2};
    initialize(line, 1, line1_name, line1_time, map, sta_name);
    vector<string> line2_name = { "浦东国际机场"	,"海天三路"	,"远东大道"	,"凌空路"	,"川沙"	,"华夏东路"	,"创新中路"	,"唐镇"	,"广兰路"	,"金科路"	,"张江高科"	,"龙阳路"	,"世纪公园"	,"上海科技馆"	,"世纪大道"	,"东昌路"	,"陆家嘴"	,"南京东路"	,"人民广场"	,"南京西路"	,"静安寺"	,"江苏路"	,"中山公园"	,"娄山关路"	,"威宁路"	,"北新泾"	,"淞虹路"	,"虹桥2号航站楼 "	,"虹桥火车站"	,"徐泾东"};
    vector<int> line2_time = { 3,	7,	3,	3,	5,	3,	3,	5,	3,	2,	4,	2,	3,	3,	3,	2,	3,	3,	3,	3,	2,	3,	3,	3,	3,	2,	7,	2,	2};
    initialize(line, 2, line2_name, line2_time, map, sta_name);
    vector<string> line3_name = { "上海南站"	,"石龙路"	,"龙漕路"	,"漕溪路"	,"宜山路"	,"虹桥路"	,"延安西路"	,"中山公园"	,"金沙江路"	,"曹杨路"	,"镇坪路"	,"中潭路"	,"上海火车站"	,"宝山路"	,"东宝兴路"	,"虹口足球场"	,"赤峰路"	,"大柏树"	,"江湾镇"	,"殷高西路"	,"长江南路"	,"淞发路"	,"张华浜"	,"淞滨路"	,"水产路"	,"宝杨路"	,"友谊路"	,"铁力路"	,"江杨北路"};
    vector<int> line3_time = { 2	,3	,2	,2	,2	,3	,2	,2	,2	,3	,2	,3	,3	,2	,3	,2	,2	,3	,2	,3	,2	,3	,2	,2	,3	,2	,2	,3};
    initialize(line, 3, line3_name, line3_time, map, sta_name);
    vector<string> line4_name = { "宜山路"	,"上海体育馆"	,"上海体育场"	,"东安路"	,"大木桥路"	,"鲁班路"	,"西藏南路"	,"南浦大桥"	,"塘桥"	,"蓝村路"	,"浦电路4"	,"世纪大道"	,"浦东大道"	,"杨树浦路"	,"大连路"	,"临平路"	,"海伦路"	,"宝山路"};
    vector<int> line4_time = { 2	,2	,2	,1	,2	,3	,2	,3	,2	,2	,2	,3	,2	,2	,2	,2	,3};
    initialize(line, 4, line4_name, line4_time, map, sta_name);
    vector<string> line5_name = { "莘庄"	,"春申路"	,"银都路"	,"颛桥"	,"北桥"	,"剑川路"	,"东川路"	,"金平路"	,"华宁路"	,"文井路"	,"闵行开发区"};
    vector<int> line5_time = { 2	,2	,4	,3	,3	,2	,3	,2	,3	,2};
    initialize(line, 5, line5_name, line5_time, map, sta_name);
    vector<string> line6_name = { "港城路"	,"外高桥保税区北"	,"航津路"	,"外高桥保税区南"	,"洲海路"	,"五洲大道"	,"东靖路"	,"巨峰路"	,"五莲路"	,"博兴路"	,"金桥路"	,"云山路"	,"德平路"	,"北洋泾路"	,"民生路"	,"源深体育中心"	,"世纪大道"	,"浦电路6"	,"蓝村路"	,"上海儿童医学中心"	,"临沂新村"	,"高科西路"	,"东明路"	,"高青路"	,"华夏西路"	,"上南路"	,"灵岩南路"	,"东方体育中心"};
    vector<int> line6_time = { 2	,3	,3	,3	,2	,2	,2	,2	,3	,2	,2	,3	,2	,2	,3	,2	,3	,2	,3	,2	,3	,2	,3	,2	,2	,2	,2};
    initialize(line, 6, line6_name, line6_time, map, sta_name);
    vector<string> line7_name = { "花木路"	,"龙阳路"	,"芳华路"	,"锦绣路"	,"杨高南路"	,"高科西路"	,"云台路"	,"耀华路"	,"长清路"	,"后滩"	,"龙华中路"	,"东安路"	,"肇嘉浜路"	,"常熟路"	,"静安寺"	,"昌平路"	,"长寿路"	,"镇坪路"	,"岚皋路"	,"新村路"	,"大华三路"	,"行知路"	,"大场镇"	,"场中路"	,"上大路"	,"南陈路"	,"上海大学"	,"祁华路"	,"顾村公园"	,"刘行"	,"潘广路"	,"罗南新村"	,"美兰湖"};
    vector<int> line7_time = { 3	,2	,3	,2	,3	,2	,2	,2	,2	,3	,2	,2	,3	,2	,3	,2	,2	,3	,2	,2	,2	,2	,3	,2	,2	,3	,3	,3	,3	,2	,4	,2};
    initialize(line, 7, line7_name, line7_time, map, sta_name);
    vector<string> line8_name = { "沈杜公路"	,"联航路"	,"江月路"	,"浦江镇"	,"芦恒路"	,"凌兆新村"	,"东方体育中心"	,"杨思"	,"成山路"	,"耀华路"	,"中华艺术宫"	,"西藏南路"	,"陆家浜路"	,"老西门"	,"大世界"	,"人民广场"	,"曲阜路"	,"中兴路"	,"西藏北路"	,"虹口足球场"	,"曲阳路"	,"四平路"	,"鞍山新村"	,"江浦路"	,"黄兴路"	,"延吉中路"	,"黄兴公园"	,"翔殷路"	,"嫩江路"	,"市光路"};
    vector<int> line8_time = { 2	,2	,2	,4	,3	,4	,2	,2	,2	,2	,3	,2	,2	,2	,2	,2	,2	,3	,2	,3	,2	,2	,2	,2	,2	,2	,2	,2	,2};
    initialize(line, 8, line8_name, line8_time, map, sta_name);
    vector<string> line9_name = { "曹路"	,"民雷路"	,"顾唐路"	,"金海路"	,"金吉路"	,"金桥"	,"台儿庄路"	,"蓝天路"	,"芳甸路"	,"杨高中路"	,"世纪大道"	,"商城路"	,"小南门"	,"陆家浜路"	,"马当路"	,"打浦桥"	,"嘉善路"	,"肇嘉浜路"	,"徐家汇"	,"宜山路"	,"桂林路"	,"漕河泾开发区"	,"合川路"	,"星中路"	,"七宝"	,"中春路"	,"九亭"	,"泗泾"	,"佘山"	,"洞泾"	,"松江大学城"	,"松江新城"	,"松江体育中心"	,"醉白池"	,"松江南站"};
    vector<int> line9_time = { 2	,3	,3	,2	,3	,3	,3	,4	,2	,4	,2	,4	,3	,2	,2	,2	,2	,3	,3	,3	,3	,2	,3	,3	,3	,4	,6	,5	,3	,4	,4	,3	,3	,3};
    initialize(line, 9, line9_name, line9_time, map, sta_name);
    vector<string> line10_name = { "新江湾城"	,"殷高东路"	,"三门路"	,"江湾体育场"	,"五角场"	,"国权路"	,"同济大学"	,"四平路"	,"邮电新村"	,"海伦路"	,"四川北路"	,"天潼路"	,"南京东路"	,"豫园"	,"老西门"	,"新天地"	,"陕西南路"	,"上海图书馆"	,"交通大学"	,"虹桥路"	,"宋园路"	,"伊犁路"	,"水城路"	,"龙溪路"	,"上海动物园"	,"虹桥1号航站楼"	,"虹桥2号航站楼"	,"虹桥火车站"};
    vector<int> line10_time = { 1	,2	,2	,2	,2	,2	,2	,2	,2	,2	,2	,2	,2	,3	,2	,3	,2	,2	,2	,2	,2	,2	,2	,3	,2	,3	,2};
    initialize(line, 10, line10_name, line10_time, map, sta_name);
    vector<string> line10_2_name = { "龙溪路"	,"龙柏新村"	,"紫藤路"	,"航中路" };
    vector<int> line10_2_time = {4,2,2};
    initialize(line, 10, line10_2_name, line10_2_time, map, sta_name);
    vector<string> line11_name = { "迪士尼"	,"康新公路"	,"秀沿路"	,"罗山路"	,"御桥"	,"浦三路"	,"三林东"	,"三林"	,"东方体育中心"	,"龙耀路"	,"云锦路"	,"龙华"	,"上海游泳馆"	,"徐家汇"	,"交通大学"	,"江苏路"	,"隆德路"	,"曹杨路"	,"枫桥路"	,"真如"	,"上海西站"	,"李子园"	,"祁连山路"	,"武威路"	,"桃浦新村"	,"南翔"	,"马陆"	,"嘉定新城"	,"白银路"	,"嘉定西"	,"嘉定北"};
    vector<int> line11_time = { 4	,3	,3	,3	,4	,3	,2	,5	,3	,2	,2	,2	,4	,2	,4	,2	,3	,1	,3	,2	,3	,2	,2	,3	,4	,5	,4	,2	,4	,3};
    initialize(line, 11, line11_name, line11_time, map, sta_name);
    vector<string> line11_2_name = { "嘉定新城"	,"上海赛车场"	,"昌吉东路"	,"上海汽车城"	,"安亭"	,"兆丰路"	,"光明路"	,"花桥"};
    vector<int> line11_2_time = {4,5,3,3,3,4,2};
    initialize(line, 11, line11_2_name, line11_2_time, map, sta_name);
    vector<string> line12_name = { "金海路"	,"申江路"	,"金京路"	,"杨高北路"	,"巨峰路"	,"东陆路"	,"复兴岛"	,"爱国路"	,"隆昌路"	,"宁国路"	,"江浦公园"	,"大连路"	,"提篮桥"	,"国际客运中心"	,"天潼路"	,"曲阜路"	,"汉中路"	,"南京西路"	,"陕西南路"	,"嘉善路"	,"大木桥路"	,"龙华中路"	,"龙华"	,"龙漕路"	,"漕宝路"	,"桂林公园"	,"虹漕路"	,"虹梅路"	,"东兰路"	,"顾戴路"	,"虹莘路"	,"七莘路"};
    vector<int> line12_time = { 4	,2	,2	,3	,2	,3	,2	,2	,3	,2	,2	,2	,2	,4	,2	,3	,3	,3	,2	,3	,2	,3	,3	,2	,2	,2	,3	,2	,3	,2	,2};
    initialize(line, 12, line12_name, line12_time, map, sta_name);
    vector<string> line13_name = { "金运路"	,"金沙江西路"	,"丰庄"	,"祁连山南路"	,"真北路"	,"大渡河路"	,"金沙江路"	,"隆德路"	,"武宁路"	,"长寿路"	,"江宁路"	,"汉中路"	,"自然博物馆"	,"南京西路"	,"淮海中路"	,"新天地"	,"马当路"	,"世博会博物馆"	,"世博大道"};
    vector<int> line13_time = { 2	,4	,3	,2	,3	,4	,2	,3	,2	,2	,3	,1	,3	,2	,3	,2	,2	,3};
    initialize(line, 13, line13_name, line13_time, map, sta_name);
    vector<string> line16_name = { "滴水湖"	,"临港大道"	,"书院"	,"惠南东"	,"惠南"	,"野生动物园"	,"新场"	,"航头东"	,"鹤沙航城"	,"周浦东"	,"罗山路"	,"华夏中路"	,"龙阳路"};
    vector<int> line16_time = { 3,6	,10	,5	,8	,7	,6	,4	,6	,7	,4	,5};
    initialize(line, 16, line16_name, line16_time, map, sta_name);
    vector<string> line17_name = { "虹桥火车站"	,"诸光路"	,"蟠龙路"	,"徐盈路"	,"徐泾北城"	,"嘉松中路"	,"赵巷"	,"汇金路"	,"青浦新城"	,"漕盈路"	,"淀山湖大道"	,"朱家角"	,"东方绿洲"};
    vector<int> line17_time = { 3	,2	,3	,3	,3	,3	,4	,3	,4	,4	,5	,3};
    initialize(line, 17, line17_name, line17_time, map, sta_name);
    int Dist[Maxsize];
    int Pre[Maxsize];
    int S[Maxsize];
    string departure;
    string destination;
    printf("input departure:\n");
    getline(cin, departure);
    printf("input destination:\n");
    getline(cin, destination);
    int d1 = sta_pos(sta_name, departure);
    int d2 = sta_pos(sta_name, destination);
    if (d1 == -1 || d2 == -1)
    {
        printf("输入了不存在的站点名\n");
        return 0;
    }
    if (d1 == d2)
    {
        printf("已到站\n");
        return 0;
    }
    ShortestPath(map,d1, Dist, Pre, S);
    output(map,sta_name, destination, Pre, d1, d2, line);
    system("pause");
	return 0;
}
