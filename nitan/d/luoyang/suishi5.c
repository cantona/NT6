inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
一條碎石小路，剛下過雨，路面看起來還滿乾淨的．一些鄉下人挑着
自己種的蔬菜到城裏來賣，人不是很多，吆喝聲傳出很遠。路中央有一兩
個乞丐正在行乞，無家可歸的人正四處遊蕩，從這裏可以看出洛陽的另一
面。路的兩邊都是當地的一些民宅。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"suishi4",
                  "west" : __DIR__"suishi6",
        ]));

	set("coor/x", -6970);
	set("coor/y", 2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}