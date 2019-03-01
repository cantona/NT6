// shanlu1.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這條山路盤著終南山主峰而上，山路貼著石璧鑿出，只容許一人得
過，形勢極為險峻。往遠處望去。群山環繞，列於腳下，百裡美景盡收
眼底，頓時令人豪氣陡聲，想要長嘯一聲。往南下是一片空地。往北上
就是終南山主峰。
LONG        );
        set("outdoors", "gumu");
        set("exits", ([
                "southdown" : __DIR__"kongdi",
                "northup"   : __DIR__"zhufeng",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", 100);
        set("coor/z", 180);
        setup();
        replace_program(ROOM);
}