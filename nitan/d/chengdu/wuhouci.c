// Room: wuhouci.c
// Date: Feb.14 1998 by Java

inherit ROOM;
string look_gaoshi();
void create()
{
        set("short", "諸葛亮殿");
        set("long", @LONG
這裡是武侯祠的正殿諸葛亮殿。武侯羽扇綸巾一如生前。兩邊諸
葛瞻和諸葛尚父子塑像也栩栩如生。掛在殿門兩壁的，由詩聖杜甫筆
下流露的千古名聯：『三顧頻繁天下事，兩朝開濟老臣心。』道盡了
這個千古風范的一生心事。
LONG );
        set("exits", ([
            "southdown" : __DIR__"liubeidian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15240);
	set("coor/y", -1840);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}