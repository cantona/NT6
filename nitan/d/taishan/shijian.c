// Room: /d/taishan/shijian.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "試劍石");
        set("long", @LONG
經刻西北有巨石，高約兩丈，寬近五丈，石辟為兩半，上題“試劍
石”三字，又名仙峽石。萬恭于明隆慶年間依崖築石亭，柱聯：“天門
倒瀉一簾雨，梵石靈呵千載文。”崖摩刻《高山流水亭記》。萬歷年間
崔應麒摩刻草書《曬經石水簾詩》：“曬經石上水簾泉，誰挽銀河落半
天。新月控鉤朝掛玉，長風吹浪暮疑煙。梵音濺沫幹還濕，曲澗流雲斷
復連。選勝具觴恣幽賞，題詩愧乏筆如椽。”
LONG );
        set("exits", ([
                "southeast" : __DIR__"jingshi",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 140);
	set("coor/z", 60);
	setup();
        replace_program(ROOM);
}