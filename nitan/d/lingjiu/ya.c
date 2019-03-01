inherit ROOM;

void create()
{
        set("short", "斷魂崖");
        set("long", @LONG
這是通向靈鷲宮的必經之路，一條小道蜿蜒曲折地通向縹緲峰頂。
路的右側是一條陡峭的山崖，一陣山風吹過，你似乎聽見從下面傳來
幾聲慘號，你心中一凜，不禁加快腳步趕緊離開這裡。
LONG );
        set("outdoors", "lingjiu");
        set("exits",([
                "westup"   : __DIR__"yan",
                "eastdown" : __DIR__"shanjiao",
        ]));
        setup();
        replace_program(ROOM);
}