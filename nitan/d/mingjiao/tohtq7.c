//TOHTQ7.C

inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
山洞中似乎深不可測，洞壁上點著幾盞鬆明，照得洞內一派光亮。
洞內雖然感到十分潮濕，可洞壁幹燥堅實，大異平常。
LONG );
        set("exits", ([
                "north" :__DIR__"tohtq7",
                "west"  :__DIR__"tohtq5",
        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}