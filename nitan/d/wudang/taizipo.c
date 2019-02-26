inherit ROOM;

void create()
{
        set("short", "太子坡");
        set("long", @LONG
此處地處坡陀之隘，形勢險要，相傳淨樂國太子少年真武入山修
道時，曾在此留住讀書，故名叫太子坡，好像一朵出水芙蓉，湧出綠
波，瓣萼歷歷可數。遠處峯迴路轉，忽明忽滅盡在雲霧之中。
LONG );
        set("exits", ([
                "northdown"  : __DIR__"shanlu1",
                "southdown"  : __DIR__"shiliang",
                "east"       : __DIR__"fuzhenguan",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -240);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}