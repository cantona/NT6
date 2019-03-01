//Room: /d/dali/dianchi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","滇池");
        set("long", @LONG
滇池四周的山脈均屬昆侖山系，雲嶺山脈的東支逶迤南下，總稱
烏蒙山，有大小數十個山峰。湖身緊靠西山腳下，山環水抱，天光雲
影，構成天然的圖畫。滇池的『滇』在彝語中即是大壩子，兼司馬遷
的《史記﹒西南夷列傳》記載，在古代就是這一地區的最大的部族名
稱，是名滇池。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"   : "/d/dali/dasenlin",
            "south"   : "/d/dali/yanchi1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19080);
	set("coor/y", -6860);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}