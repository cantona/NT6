// Room: /d/yanping/xita.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "西塔");
        set("long", @LONG
西塔竣于明萬歷三十五年六月，矗立于九龍巖頂，高七丈，七層八
角，實心青石構築。須彌基座雕式精美，基座外石廊上有龍、鹿和花草
浮雕，栩栩如生。塔之六層有二石匾(bian)，二層另有一“蛟騰鳳起”
石匾，相傳建塔本為鎮妖。
LONG );
        set("exits", ([
                "southwest"    : __DIR__"yuandong",
        ]));
        set("item_desc", ([
                "bian" : "
民       文
財       運
永       遐
阜       昌\n\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yanping");
        setup();
        replace_program(ROOM);
}