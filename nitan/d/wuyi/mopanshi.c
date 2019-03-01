// Room: /d/wuyi/mopanshi.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "磨盤石");
        set("long", @LONG
磨盤石在八曲之南。兩塊橢圓而挺拔的巨石疊合在一起，狀如一副
磨盤。經雨水沖刷而形成的一束束乳白的漿液從磨盤的中央裂縫中汨汨
往下流淌，真切而動感。宋朝李綱詩曰：“仙家何事也儲糧，石廩團團
曲水傍。應駕玉龍耕紫石，瓊芝千畝個中藏。”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northdown" : __DIR__"8qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1330);
        set("coor/y", -5030);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
