// Room: /guiyun/jinship.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "金國戰船");
        set("long", @LONG
這裡是大金國欽使的戰船，船中旗桿上分明扯著旗號，飛揚跋
扈已極。船艙內漢姦們一臉媚笑，金兵一個個都趾高氣揚。
LONG );
        set("outdoors", "guiyun");
        set("exits", ([
                "out" : __DIR__"ship",
        ]));
        set("objects", ([
                "/d/huanghe/npc/peng" : random(2),
                "/d/huanghe/npc/sha" : random(2),
                "/d/huanghe/npc/liang" : random(2),
                "/d/huanghe/npc/hou" : random(2),
                "/d/huanghe/npc/ma" : random(2),
                "/d/huanghe/npc/qian" : random(2),
                "/d/huanghe/npc/shen" : random(2),
                "/d/huanghe/npc/wu" : random(2),
                "/kungfu/class/xueshan/lingzhi" : random(2),
                "/d/guiyun/npc/ouyangfeng" : random(2),
                //"/kungfu/class/ouyang/ouyangke" : random(2),
                __DIR__"npc/duantiande" : random(2),
                __DIR__"npc/wanyankang" : random(2),
                __DIR__"npc/wanyanhonglie" : random(2),
                __DIR__"npc/jinbing" : random(4),
        ]));
        set("coor/x", 300);
        set("coor/y", -700);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}