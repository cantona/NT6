//LUCAS 2000-6-18
// wallw1.c

inherit ROOM;

void create()
{
        set("short", "城頭");
        set("long", @LONG
狂風吹雪，捲起千堆銀屑。孤鴻翔空，拂亂萬里雲空。“平
地不見雪，白沙入黃雲”，正是這種情況的真實寫照。遠處依稀
可見一兩個在當地被稱為‘海子’的湖泊，在狂風、白雪、烈日
的映照下，掛起點點魚鱗之浪。
LONG );
        set("outdoors", "lingxiao");
        set("no_clean_up", 0);

        set("exits", ([
                "west" : __DIR__"wallw2",
                "eastdown"  : __DIR__"gate",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 1,
        ])); 
        setup();
        replace_program(ROOM);
}
