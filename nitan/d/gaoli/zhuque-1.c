// /d/gaoli/zhuquedajie1
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "得勝大街");
        set("long", @LONG
你走在一條寬闊的石板大街上，北面就快到高麗皇宮了。都可以看
見皇宮的圍牆拉南面是高麗的南門得勝門，東面是高麗最大的酒樓，西
面是一家珠寶店，專賣各式各樣的首飾。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"zhuque-2",
                "north" : __DIR__"yudao1",
                "east":__DIR__"jiulou",
                "west":__DIR__"zhubaodian",    
        ]));
       setup();
        replace_program(ROOM);
}        
