#include <ansi.h>
inherit NPC;
int check_legal_name(string arg);
int check_legal_id(string arg);

void create()
{
        set_name("瀟江", ({ "xiaojiang" }) );
        set("gender", "女性" );
        set("age", 22);
        set("long","瀟江姓顧，後嫁給一小土財主，財主過世後就開使每天背一個小筐賣（ｙａｎｇ）寵物\n");
        set("combat_exp", 5);
        set("chat_chance", 15);
        set("chat_msg", ({
                (: random_move :)
        }) );
        set("attitude", "friendly");
        setup();

}

void init()
{       
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_yang", "yang");

}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "瀟江說道：這位" + RANK_D->query_respect(ob)
                                + "，要買小貓小狗麼？\n");
                        break;
                case 1:
                        say( "瀟江說道：這位" + RANK_D->query_respect(ob)
                                + "，你太窮酸了，我不賣給你。\n");
                        break;
        }
}

int do_yang(string arg)
{
        string ctype, cname, ccolor, cid;
        object ob, me, gold;
        string id,filename;
        object newpet;
        me = this_player();
        id=query("id", me);
        if(!arg || sscanf(arg,"%s %s %s %s",ctype,ccolor,cname,cid ) != 4)
        return notify_fail("指令格式：yang <type> <color> <name> <english name>\n");
        if(me->is_busy())
        return notify_fail("你上一個動作還沒有完成。\n");
        if(file_size( me->query_save_file() + ".pet.o") > 0)
        return notify_fail("你已經擁有你心愛的寵物了。\n");
        gold = present("gold_money", this_player());
        if(!gold) return notify_fail("你身上沒有金子。\n");
        if((int) gold->query_amount() < 100)
        return notify_fail("你身上沒有那麼多金子。\n");
        if( query("score", me)<500 )
        return notify_fail("你的評價不夠。\n");
        if( !check_legal_name(cname))
        return notify_fail("");
        if( !check_legal_id(cid))
        return notify_fail("");

        if( ccolor != "$BLK$" && 
            ccolor != "$NOR$" &&
            ccolor != "$RED$" &&
            ccolor != "$GRN$" &&
            ccolor != "$YEL$" &&
            ccolor != "$BLU$" &&
            ccolor != "$MAG$" &&
            ccolor != "$CYN$" &&
            ccolor != "$WHT$" &&
            ccolor != "$NOR$" &&
            ccolor != "$HIR$" &&
            ccolor != "$HIG$" &&
            ccolor != "$HIY$" &&
            ccolor != "$HIB$" &&
            ccolor != "$HIM$" &&
            ccolor != "$HIC$" &&
            ccolor != "$HIW$" 
        )
        return notify_fail("不知你要什麼顏色．\n");
        cname = ccolor + cname;
        cname = replace_string(cname, "$BLK$", BLK);
        cname = replace_string(cname, "$RED$", RED);
        cname = replace_string(cname, "$GRN$", GRN);
        cname = replace_string(cname, "$YEL$", YEL);
        cname = replace_string(cname, "$BLU$", BLU);
        cname = replace_string(cname, "$MAG$", MAG);
        cname = replace_string(cname, "$CYN$", CYN);
        cname = replace_string(cname, "$WHT$", WHT);
        cname = replace_string(cname, "$HIR$", HIR);
        cname = replace_string(cname, "$HIG$", HIG);
        cname = replace_string(cname, "$HIY$", HIY);
        cname = replace_string(cname, "$HIB$", HIB);
        cname = replace_string(cname, "$HIM$", HIM);
        cname = replace_string(cname, "$HIC$", HIC);
        cname = replace_string(cname, "$HIW$", HIW);
        cname = replace_string(cname, "$NOR$", NOR);
        cname += NOR;
        seteuid(ROOT_UID);
        newpet = new("/quest/tulong/obj/pet");       
        switch( ctype ) {
                case "dog":
                        set("title", "小狗", newpet);
                        set("int", 5+random(10), newpet);
                        break;
                case "cat":
                        set("title", "小貓", newpet);
                        set("per", 5+random(10), newpet);
                        break;
                case "pig":
                        set("title", "小豬", newpet);
                        set("str", 5+random(10), newpet);
                        break;
                case "monkey":
                        set("title", "小猴", newpet);
                        set("dex", 5+random(10), newpet);
                        break;
                case "duck":
                        set("title", "小鴨", newpet);
                        set("con", 5+random(10), newpet);
                        break;
                case "hen":
                        set("title", "小雞", newpet);
                        set("kar", 5+random(10), newpet);
                        break;
                case "hawk":
                        set("title", "小鷹", newpet);
                        set("dex", 5+random(2), newpet);
                        break;
                default:
                        return notify_fail("這裡沒有你要的東西．\n");
        }
        set("owner",query("id",  me), newpet);
        set("possessed", me, newpet);
        set("name", cname, newpet);
        set("id", cid, newpet);
        newpet->save();
        destruct(newpet);
        gold->add_amount(-100);
        addn("score", -500, me);
        me->start_busy(1);
        command("say 你試著吹一聲口哨（ｗｈｉｓｔｌｅ），你的小寶寶就會跑過來的！\n");
        seteuid(getuid());
        return 1;
}
int check_legal_name(string name)
{
        int i;
        i = strlen(name);
        if( (strlen(name) < 2) || (strlen(name) > 40 ) ) {
                write("對不起，中文名字必須是一到二十個中文字。\n");
                return 0;
        }
        while(i--) {
                if( name[i]<=' ' ) {
                        write("對不起，中文名字不能用控制字元。\n");
                        return 0;
                }
                if( i%2==0 && !is_chinese(name[i..<0]) ) {
                        write("對不起，名字必需是中文。\n");
                        return 0;
                }
        }
        return 1;
}

int check_legal_id(string name)
{
        int i;
        i = strlen(name);
        if( (strlen(name) < 3) || (strlen(name) > 20 ) ) {
                write("對不起，英文名字必須是三到二十個字。\n");
                return 0;
        }

        return 1;
}
