// Room: /d/suzhou/shiyuan.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "石黿");
        set("long",@long
這是一塊突出平地的巨石，稱為“石黿”。石黿背面刻著“望佛來
”三個字，背上凹痕處，傳說是夫差與西施立石昂首眺望太湖石留下的
腳印。從石黿旁俯視，左右有兩個水窪。
long);
        set("outdoors", "suzhou");
        set("objects",([
                __DIR__"npc/ke" : 2,
        ]));
        set("exits",([
                "southup" : __DIR__"lingyansi",
                "westdown" : __DIR__"shuiwa1",
                "eastdown" : __DIR__"shuiwa",
                "northdown" : __DIR__"yingxiaoting",
                "southwest" : __DIR__"mubei",
        ]));
	set("coor/x", 1120);
	set("coor/y", -1150);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}