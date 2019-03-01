//TOHTQ5.C

inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
山洞中似乎深不可測，洞壁上點着幾盞松明，照得洞內一派光亮。
洞內雖然感到十分潮濕，可洞壁乾燥堅實，大異平常。
LONG );
        set("exits", ([
                "east"  :__DIR__"tohtq6",
                "south" :__DIR__"tohtq4",
                "west" :__DIR__"didao/didao",
        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}