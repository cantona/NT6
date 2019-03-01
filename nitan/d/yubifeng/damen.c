// /yubifeng/damen.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "山莊大門");
        set("long", @long
轉過了幾株雪鬆，只見前面一座五開間極大的石屋，屋前屋後都是
白雪。大門外寫著“玉筆峰山莊”幾個大字，此處氣候酷寒，上下艱難，
當初不知道莊主花了多少的心思才能在此建成如此石室，不禁令人嘖嘖
稱奇。
long );
        set("exits", ([
                "west"  : __DIR__"fengding",
                "enter" : __DIR__"changlang",
        ]));
        set("objects", ([
                __DIR__"npc/caoyunqi" : 1,
                __DIR__"npc/zhouyunyang" : 1,
                __DIR__"npc/ruanshizhong" : 1,
                __DIR__"npc/yinji" : 1,
        ]));
        set("outdoors", "yubifeng");
        set("coor/x", 6120);
        set("coor/y", 5170);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}