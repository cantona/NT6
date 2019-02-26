// shanshui.c
// Last Modified by winder on Nov. 17 2000

inherit ITEM;

int do_jiao(string arg);

void create()
{
        set_name("山水畫", ({ "shanshui hua", "shanshui", "hua" }) );
        set("long","
只見畫中是一座陡峭突兀的高山，共有五座山峯，中間一峯尤高，
筆立指天，聳入雲表，山側生着一排松樹，鬆梢積雪，樹身盡皆向南彎
曲，想見北風之烈。峯西獨有一棵老鬆，卻是挺然直起，巍巍秀拔，樹
下硃筆畫着一個迎風舞劍的將軍。這人面目難見，但衣袂飄舉，資形脱
俗。全幅畫都是水墨山水，獨此人殷紅如火，更加顯得卓犖不羣。畫上
並無書款，只題着一首詩云：“經年塵土滿征衣，特特尋芳上翠微，好
山好水看不足，馬蹄催趁月明歸。”
");
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "幅");
        }
        setup();
}

void init()
{
        add_action("do_jiao","water");
        add_action("do_jiao","jiao");
}

int do_jiao(string arg)
{
        object me=this_player();
        object* inv;
        int i, remaining;

        if (!id(arg)) return 0;
        inv = all_inventory(me);
        for (i = 0; i < sizeof(inv); i++) {
                if( mapp(query("liquid", inv[i]))){
                        if( (remaining=query("liquid/remaining", inv[i]))>0){
                                write("你從"+query("name", inv[i])+"裏倒出些"+query("liquid/name", inv[i])+"來，塗在畫上。\n");
                                write("忽見畫的右下角依稀露出幾行字跡：“..穆遺書，..鐵掌..，中....峯，第二..節。”\n");
                                set_temp("wumu_shanshui", 1, me);
                                remaining--;
                                set("liquid/remaining", remaining, inv[i]);
                                return 1;
                        }
                        else {
                                write("你的"+query("name", inv[i])+"已經空了，再也擠不出一滴"+query("liquid/name", inv[i])+"了！\n");
                                return 1;
                        }
                }
        }
        write("你的身上沒有帶盛水的器具！\n");
        return 1;
}