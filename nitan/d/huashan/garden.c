//garden.c
inherit ROOM;
void create()
{
        set("short","花園");
        set("long", @LONG
這是一個園子，庭院清幽，異種花卉甚是不少。百花爭放，山石
古拙，楊柳垂清，蒼松翠竹，景緻煞是宜人。清澈的溪流旁聳立着一
座小亭子，潺潺溪水向西南流去。東面通往有所不為軒，北面是一條
長廊，西邊小屋傳出陣陣香味，引得你真想去看看。
LONG );
        set("exits",([
                "east"      : __DIR__"buwei1",
                "west"      : __DIR__"chufang",
                "north"     : __DIR__"changlang",
                "south"     : __DIR__"shufang",
                "southwest" : __DIR__"houyuan",
        ]));
        set("outdoors", "huashan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
 