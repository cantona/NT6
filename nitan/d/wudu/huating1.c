inherit ROOM;

void create()
{
        set("short", "花廳");
        set("long", @LONG
這裏是一個幽雅別緻的花廳，四周掛着碧紗的幔帳，屋角香爐中
飄着一股奇異的香氣。有一個粉紅衣裙的少女正坐在窗邊發呆，聽見
腳步聲不覺瞟了你一樣，秀眉微微一顰，似乎不太高興。
LONG);

        set("exits", ([
                "south" : __DIR__"huating2",
                "west" : __DIR__"huayuan1",
                "north" : __DIR__"huating3",
        ]));
        set("objects", ([
                CLASS_D("wudu") + "/hetieshou" : 1,
        ]));

        setup();
        replace_program(ROOM);
}