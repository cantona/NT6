inherit ROOM;

void create()
{
      set("short", "卧雲庵");
        set("long", @LONG
卧雲庵旁邊有個井絡泉，據説以前曾因飲水人多了而乾涸，眾尼
為之誦經，於是泉水復出。出了卧雲庵便是睹光台，旁邊便是華藏庵。
LONG );
        set("objects", ([
                CLASS_D("emei") + "/xuan" : 1,
        ]));
        set("outdoors", "emei");
        set("exits", ([
                "northeast" : __DIR__"jinding", 
                "southeast" : __DIR__"duguangtai", 
        ]));
        set("coor/x", -580);
        set("coor/y", -320);
        set("coor/z", 220);
        setup();
        replace_program(ROOM);
}