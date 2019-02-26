// Room: /u/zqb/tiezhang/shanjiao.c

inherit ROOM;

void create()
{
        set("short", "山腳下");
        set("long", @LONG
這裏已到了山腳下，此處近看，但見五座山峯峭兀突怒，確似五根手指
豎立在半空之中。居中一峯尤見挺拔，筆立指天，聳入雲表，下臨深澗。山
側生着一片松林，鬆梢留雪，樹身盡皆向南彎曲，想見北風極烈。
LONG        );
    set("outdoors", "tiezhang");
        set("exits", ([ /* sizeof() == 2 */
  "northup" : __DIR__"shanmen",
  "southeast" : __DIR__"road-3",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}