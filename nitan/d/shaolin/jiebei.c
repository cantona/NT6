// Room: /d/shaolin/jiebei.c
// Date: YZC 96/01/19

inherit ROOM;

string look_jiebei();

void create()
{
        set("short", "界碑");
        set("long", @LONG
界碑──未連接好的區域(jiebei)。
LONG );

        set("exits", ([
                "east" : __DIR__"shulin14",
                "northup" : __DIR__"qyping",
        ]));

        set("outdoors", "shaolin");
        set("item_desc",([
                "stone"                :        (: look_jiebei :),
        ]));
        setup();
}


string look_jiebei()
{
        return "由此往前，通向山頂。道路尚未修好。\n─時空書于俠客行\n";
}