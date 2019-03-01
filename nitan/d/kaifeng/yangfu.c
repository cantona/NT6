inherit ROOM;

void create()
{
        set("short", "天波揚府");
        set("long", @LONG
天波揚府是抗遼名將楊業的府邸，自從揚業去世之後，府中只剩
下一些女子居住。門前的綠柳槐樹旁，兩塊大石光滑異常，乃是當朝
所賜。文官過者下橋，武官過者下馬。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"road3",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5070);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}