inherit ROOM;

void create()
{
        set("short", "上山小路");
        set("long", @LONG
這是一條上山的小路，腳下是青石砌成的台階，濕漉漉的長滿了
青苔，四周全是茂密的竹林。遠處傳來一陣悠揚的山歌聲。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "southup" : __DIR__"shanlu3",
                "northdown" : __DIR__"xiaolu",
        ]));

        setup();
        replace_program(ROOM);
}