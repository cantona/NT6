//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "菜田");
        set("long", @LONG
這是一塊菜地，但見一片青綠，都種滿了空心菜。白色的蛾蝶在菜
叢中上下飛舞。“空心菜”是湘西一帶最尋常的蔬菜，粗生粗長，菜莖
的心是空的。給人取了這個綽號，就是笑人直肚直腸，沒半點心事的意
思。
LONG );
        set("exits", ([
                "west"     : __DIR__"maxipu",
        ]));
        set("objects", ([
                __DIR__"npc/diyun" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("coor/x", -7110);
	set("coor/y", -2180);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}