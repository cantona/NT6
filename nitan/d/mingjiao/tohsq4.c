//TOHSQ4.C

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
山路到這裡似乎變得寬闊了些。清新的山風撲面而來，令人精神
頓為一爽。遠處傳來淙淙水聲，漸行漸遠。山壁上掛滿了厚密的籐蘿，
隨風輕輕搖弋。
LONG );
        set("exits", ([
                "north" : __DIR__"tohsq5",
                "south" : __DIR__"tohsq2",
        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}