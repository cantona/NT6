//Room: bank.c

#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "四海錢莊");
        set("long", @LONG
這是長安城的一家老字號錢莊，老闆是山西人，這家錢莊從他的
祖先來到這裏時就開始辦起，一直傳到他的手裏。錢莊的信譽非常好，
而且在全國各地都開了分店。它發行的銀票通行全國。錢莊的門口掛
有一塊牌子(paizi)。
LONG );
        set("item_desc", ([
                "paizi": 
HIG"本錢莊提供的服務有：\n"NOR
HIC"--------------------------------\n"NOR
HIG"check(chazhang)        查帳\n"NOR 
HIC"--------------------------------\n"NOR
HIG"deposit(cun)           存款\n"NOR
HIC"--------------------------------\n"NOR
HIG"withdraw(qu)           取款\n"NOR
HIC"--------------------------------\n"NOR
HIG"convert(duihuan)       兑換錢幣\n"NOR
HIC"--------------------------------\n"NOR

        ]) );
        set("exits", 
        ([ //sizeof() == 1
                "south" : "/d/changan/qixiang4",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/tiegongji" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10710);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}