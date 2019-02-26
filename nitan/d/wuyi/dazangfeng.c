// Room: /d/wuyi/dazangfeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "大藏峯");
        set("long", @LONG
每次看到這座四曲南岸的大藏峯，總有一股透着玄機的冷意浸透你
的心田，讓你頓感歲月在這裏是這樣的蒼老和深邃，歷史在這裏有時如
此的厚重和迷茫。大藏峯在溪邊橫空崛起，陡峭千仞。半壁有兩個洞穴，
上穴“金窠巖”中有千年不腐的稻草，下穴“金雞洞”內有虹橋板和幾
具船棺。所謂“千古浮名都是夢，百年人事盡如斯。”。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northdown" : __DIR__"4qu",
        ]));
        set("objects", ([
                "/d/taishan/npc/shu-sheng" : 1,
        ]));
        set("coor/x", 1370);
        set("coor/y", -5020);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
