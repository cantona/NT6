// Room: /d/yueyang/xuanyuantai.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "軒轅台");
        set("long", @LONG
南有一懸崖崖下有龍虎猴三洞，崖上高處就是鑄鼎台。鑄鼎台又稱
軒轅台，傳聞軒轅黃帝曾在此鑄鼎。江湖每年的丐幫君山大會都在此處
舉行，當年黃蓉以少女之身十五歲執掌丐幫，便是在此一舉威鎮羣丐而
獲得擁戴，此等豔舉空前抑且不再，後輩英豪無緣盛舉，撫今追昔，慷
慨萬端。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "eastdown" : __DIR__"shijie6",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/ma" : 1,
        ]));
        set("coor/x", -1790);
        set("coor/y", 2270);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}
