// gudi.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "谷底");
        set("long", @LONG
但聽得耳邊轟聾聾的響聲越來越大，山崖也逐漸變得傾斜，而不再
象上面那麼陡峭筆立了，終于到達谷底了。只見上面的上崖一條大瀑布
如玉龍懸空，滾滾而下，傾入了一座清澈異常的大湖之中。瀑布注入處
湖水翻滾，只離得瀑布十餘丈，湖水便一平如鏡。
LONG );
        set("exits", ([
                "up" : __DIR__"yanfeng",
                "west" : __DIR__"hubian",
        ]));
        set("outdoors", "wuliang" );
        set("no_clean_up", 0);
        set("coor/x", -50010);
        set("coor/y", -21060);
        set("coor/z", -40);
        setup();
        replace_program(ROOM);
}