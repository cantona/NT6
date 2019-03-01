// /d/gaoli/zhuquedajie1
// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "得勝大街");
        set("long", @LONG
你走在一條寬闊的石板大街上，北面就快到高麗皇宮了。都可以看
見皇宮的圍牆拉南面是高麗的南門得勝門，東面的店舖的門外掛著一個
大大的當字，進出得人有喜有憂西面傳來吆五喝六的聲音，是高麗的一
家賭場。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"zhuquemen",
                "north" : __DIR__"zhuque-1",
                "east":__DIR__"dangpu",
                "west":__DIR__"duchang",    
        ]));
       setup();
        replace_program(ROOM);
}        
