// Room: /d/luoyang/shangqing.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "上清宮");
        set("long",  @LONG
上清宮位于邙山之巔翠雲峰，相傳這裡為太上老君煉丹處。上清宮
規模宏偉，殿堂巍峨，門外有石獅石馬。明代嘉靖十四年，道士張玄募
錢重建，以山高風大，改殿頂小瓦為大型釉瓦，屋脊置鐵瓦，故稱大殿
為鐵瓦琉璃殿。歷代文人墨客涉足山巔，南望伊洛平原，古都盡收眼底。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "southeast" : __DIR__"mangshan",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -7000);
	set("coor/y", 2280);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}