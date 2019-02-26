#include <ansi.h>
inherit NPC;

int check_legal_name(string arg);
int check_legal_id(string arg);

void create()
{
        set_name("翩翩", ({ "pian pian" }) );
        set("gender", "女性" );
        set("age", 22);
        set("long",@LONG
翩翩姓張，後嫁給一小土財主，財主過世後就開使每天背一個小筐賣寵物。你要
喜歡寵物的話，不妨也養(yang)一隻玩玩。
LONG );
        set("title",HIW"寵物小販"NOR);
        set("combat_exp", 5);
        set("chat_chance", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/cloth/cloth")->wear();

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
                        say( "翩翩説道：這位" + RANK_D->query_respect(ob)
                                + "，要買小貓小狗麼？\n");
                        break;
                case 1:
                        say( "翩翩説道：這位" + RANK_D->query_respect(ob)
                                + "，你太窮酸了，我不賣給你。\n");
                        break;
        }
}

int do_yang(string arg)
{
        string ctype, cname, ccolor, cid, ownername, result;
        object ob, me, gold;
        string id,filename;
        object newpet;

        me = this_player();
        id=query("id", me);
        ownername = me->name(1);
        
        if(!arg || sscanf(arg,"%s %s %s %s",ctype,ccolor,cname,cid ) != 4)
        {
                write(@LONG
指令格式：yang <type> <color> <name> <english name>
可以養的寵物種類有：
        小狗：dog       小貓：cat       小豬：pig       小鷹：hawk
        小猴：monkey    小鴨：duck      小雞：hen
寵物可選的顏色有：
        $RED$ - 紅色    $HIR$ - 亮紅色  $YEL$ - 土黃色
        $GRN$ - 綠色    $HIG$ - 亮綠色  $BLU$ - 深藍色
        $HIY$ - 黃色    $MAG$ - 淺紫色  $HIM$ - 粉紅色
        $HIB$ - 藍色    $HIC$ - 天青色  $CYN$ - 藍綠色
        $HIW$ - 白色    $WHT$ - 淺灰色  $NOR$ - 正常顏色
其它與寵物有關的介紹請help pet參考相關的説明。
LONG );                
                return 1;
        }
        if(me->is_busy())
                return notify_fail("你上一個動作還沒有完成。\n");
        if(file_size( me->query_save_file() + ".pet.o") > 0)
                return notify_fail("你已經擁有你心愛的寵物了。\n");
        gold = present("gold_money", this_player());
        if(!gold)
                return notify_fail("你身上沒有金子。\n");
        if((int) gold->query_amount() < 100)
                return notify_fail("你身上沒有那麼多金子。\n");
        if( query("score", me)<500 )
                return notify_fail("你的評價不夠。\n");
                
        if( (ownername != cname) && (stringp(result = NAME_D->invalid_new_name(cname))) )
        {
                write("對不起，" + result);
                write(HIR"禁止使用與他人姓名相同或接近的寵物名。並因循RULES中對名字的相關規定。"NOR+"\n");
                return 1;
        }
            
        if( !check_legal_name(cname))
                return notify_fail("");
        if( !check_legal_id(cid))
                return notify_fail("");

        if( ccolor != "$NOR$" &&
            ccolor != "$RED$" &&
            ccolor != "$GRN$" &&
            ccolor != "$YEL$" &&
            ccolor != "$BLU$" &&
            ccolor != "$MAG$" &&
            ccolor != "$CYN$" &&
            ccolor != "$WHT$" &&
            ccolor != "$HIR$" &&
            ccolor != "$HIG$" &&
            ccolor != "$HIY$" &&
            ccolor != "$HIB$" &&
            ccolor != "$HIM$" &&
            ccolor != "$HIC$" &&
            ccolor != "$HIW$" 
        )
        return
                notify_fail("不知你要什麼顏色．\n");
        cname = ccolor + cname;
        if(ccolor != "$NOR$")
        {
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
                cname += NOR;
        }
        seteuid(ROOT_UID);
        newpet = new("/clone/misc/pet");        
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
                        set("con", 5+random(10), newpet);
                        break;
                case "hawk":
                        set("title", "小鷹", newpet);
                        set("dex", 5+random(2), newpet);
                        break;
                default:
                        return notify_fail("這裏沒有你要的東西。\n");
        }
        set("owner",query("id",  me), newpet);
        set("possessed", me, newpet);
        set("name", cname, newpet);
        set("id", cid, newpet);
        set("long", "一隻"+ownername+"養的"+query("title", newpet)+"。", newpet);
        newpet->save();
        destruct(newpet);
        gold->add_amount(-100);
        addn("score", -500, me);
        me->start_busy(1);
        command("say 你試着吹一聲口哨(whistle)，你的小寶寶就會跑過來的！");
        seteuid(getuid());
        return 1;
}

int check_legal_name(string name)
{
        int i;
        i = strlen(name);
        if( (strlen(name) < 2) || (strlen(name) > 10 ) ) {
                write("對不起，中文名字必須是一到五個中文字。\n");
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
