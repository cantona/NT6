// Room: /d/mingjiao/shanlu2.c
// Date: Java 97/04/9

inherit ROOM;

void create()
{
        set("short", "青石階");
        set("long", @LONG
眼前遽然出現一大片松林。松林長得極密，石階轉向北坡，上面
鋪滿了厚厚的金黃的松針。踩在腳下，發出察察的響聲。一條窄小的
黃土小路繼續向西延伸，進入樹林深處，消失在茫茫林海之中。
LONG );
        set("exits", ([
                "eastdown" : __DIR__"shanlu1",
                "northup" : __DIR__"shanlu3",
                "west" : __DIR__"huangtulu1",
        ]));
        set("objects",([
//             __DIR__"npc/xinran":1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}
