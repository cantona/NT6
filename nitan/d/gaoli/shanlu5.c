// /d/gaoli/xuanwumen
// Room in 高麗
inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裡是一條山路。西邊就是高麗的西烽火台了。有幾個官兵在那裡
檢查來往的行人。現在時局混亂，所以這裡的戒備也是很嚴格。
LONG
        );

        set("exits", ([
                "southdown" : __DIR__"shanlu4",
                "westup":__DIR__"xifenghuotai",
        ]));

         set("outdoors", "gaoli");
        setup();
        replace_program(ROOM);
}


