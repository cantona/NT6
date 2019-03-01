// 桃谷六仙    make joke by That. Nov.6.1997
#include <ansi.h>

inherit NPC;

string *rnd_say = ({
        "我們桃谷六仙，是名震天下的六大英雄。這裏的人居然都假裝不認識我們！",
        "為什麼令狐沖這小子還沒來？又和那個小妖女混在一起了？",
        "有誰可以給我一些錢？夜貓子的一千兩銀子還我們的時候我再還給你吧！",
        "我想看看青城派的屁股向後平沙落雁式！",
        "可不可以告訴我哪裏可以大便？下次見到不戒那個臭婆娘可不會這麼大方了！",
        "方正這個老禿驢在這裏不是方丈啦？真可憐．．．",
        "那個死沖虛牛鼻子為什麼不來接我們？",
        "廈門的美眉聽説很漂亮？",
        "風兒和仙子這兩個小渾蛋幹嘛去了？",
        "快打酒來！愣什麼！",
        "快把老頭子和祖千秋拉成一堆爛肉！",
        "嶽不羣就是偽君子．．．",
        "你是任盈盈？",
        "嗨..",
});

varargs void drool(string msg, string who);

void create()
{
        string name, id;

        set_name("桃根仙", ({ "taogen xian", "gen" }) );
        set("title", "普通百姓");
        set("gender", "男性");
        set("age", 66);
        set("attitude", "friendly");
        set("combat_exp", 1000000);
        set("env/wimpy", 100);
        //set("chat_chance", 30);
        set("chat_msg", ({
                (: command("eat1") :),
                (: command("goeat") :),
                (: command("mapi1") :),
                (: command("drinkcup") :),
                (: command("ugly") :),
                (: command("mapi") :),
                (: command("slogan2") :),
                (: command("zzz") :),
                (: command("lazy") :),
                (: command("slogan") :),
                (: drool :),
                (: drool :),
                (: drool :),
                (: drool :),
                (: drool :),
                (: drool :),
        }) );
        setup();
        if( clonep() ) CHANNEL_D->register_relay_channel("chat");
}

int add_phrase(string who, string msg)
{
        msg = replace_string(msg, "?", "");
        msg = replace_string(msg, "？", "");
        msg = replace_string(msg, "？", "");
        msg = replace_string(msg, "!", "");
        msg = replace_string(msg, "！", "");
        msg = replace_string(msg, "啊", "");
        msg = replace_string(msg, "嗎", "");
        msg = replace_string(msg, "耶", "");
        msg = replace_string(msg, "吧", "");

        if( msg!="" ) {
                add("memory/" + who, ({ msg }));
                return 1;
        } else return 0;
}

string make_reply()
{
}

void relay_channel(object ob, string channel, string msg)
{
        string who, phrase;

//        if( !userp(ob) || (channel != "chat") ) return;
        who=query("name", ob);

        // Don't process our own speech.
        if( ob==this_object() ) return;

        if( add_phrase(who, msg) && random(10) > 4 && strlen(msg)<500 )
                drool(msg,query("name", ob));
}

void relay_say(object ob, string msg)
{
        string who, phrase;

        if( !userp(ob) ) return;
        who=query("name", ob);

        // Don't process our own speech
        if( ob==this_object() ) return;

        if( add_phrase(who, msg) && random(10) > 4 && strlen(msg)<500 )
                drool(msg,query("name", ob));
}

void relay_emote(object ob, string verb)
{
        if( !userp(ob) ) return;

        switch(verb)
        {

        case "kick":
                if( random(10)<5 ) {
                        command("say 為什麼踢我？會痛耶！");
                        break;
                }
        case "hug":
        case "kiss":
        case "mo":
        case "18mo":
        case "nocloth":
        if( query("gender", ob) == "男性" || 
             query("gender", ob) == "無性" )
        {
                command("chat這算啥，"+query("name", ob)+"！我就喜歡這個調調兒！\n");
                command("chat 誰想得到這" + RANK_D->query_rude(ob)+"，竟然有龍陽之好。\n");
        }
        else
        {
                command("giggle");
                command("chat想不到"+query("name", ob)+"自動把豆腐送上來了。再開心沒有了！");
        }
                message_vision("$N搖了搖頭，對$n幽幽歎道：唉，你這又是何苦呢?\n",this_object(), this_player());
        default:
                if( random(10)<5 )
                        command(verb+""+query("id", ob));
                else
                        drool();
        }
}

varargs void drool(string msg, string who)
{
        mapping mem;
        string *ob;

        mem = query("memory");
        if( !mapp(mem) ) return;

        if( !msg || !who) {
                ob = keys(mem);
                who = ob[random(sizeof(ob))];
                msg = mem[who][random(sizeof(mem[who]))];
        }

        if( (strsrch(msg, "為什麼") >= 0) ) {
                if( sscanf(msg, "%*s為什麼%s", msg)==2 ) msg = "為什麼" + msg;
                switch(random(8)) {
                case 0: command("say " + who + "，你是在問我嗎？"); break;
                case 1: command("say 關於" + msg + " ... "); break;
                case 2: command("say 呃 ... "); drool(); break;
                case 3: command("say 這個問題嘛 ...."); break;
                case 4: command("say " + who + "，知道這個問題的答案對你那麼重要麼？"); break;
                case 5: command("say " + msg + "？"); break;
                case 6: command("say " + who + "你能不能説清楚一點？"); break;
                case 7: command("say " + who + "，我不懂你問的問題"); break;
                }
        }
        else if( (strsrch(msg, "你") >= 0)
        ||      (strsrch(msg, "□") >= 0)
        ||      (strsrch(msg, "drooler") >= 0)
        ||      (strsrch(msg, "Drooler") >= 0)) {
                if( sscanf(msg, "%*s你%s", msg) == 2 ) msg = "你" + msg;
                msg = replace_string(msg, "你", "我");
                msg = replace_string(msg, "□", "我");
                switch(random(10)) {
                case 0: command("say " + who + "，你是説" + msg + "嗎？");break;
                case 1: command("say 你確定" + msg + "？");     break;
                case 2: command("say " + msg + "跟你有什麼關係？");     break;
                case 3: command("say 嗯 ... " + who + "説得好"); break;
                case 4: command("say " + who + "你為什麼對" + msg + "這麼有興趣？"); break;
                case 5: command("say 為什麼你認為" + msg + "？"); break;
                case 6: command("say 換個話題吧"); drool(); break;
                case 7: command("say 才怪"); break;
                case 8: command("say 不一定吧？"); break;
                case 9: command("say 有這個可能 ...."); break;
                }
        }
        else if( (strsrch(msg, "我") >= 0)) {
                if( sscanf(msg, "%*s我%s", msg) == 2 ) msg = "我" + msg;
                msg = replace_string(msg, "我", "你");
                msg = replace_string(msg, "?", "");
                switch(random(8)) {
                case 0: command("say 你是説" + msg + "嗎？"); break;
                case 1: command("say 真的？" + msg + "？");     break;
                case 2: command("say 如果" + msg + "，我能幫你什麼忙嗎？");break
;
                case 3: command("hmm"); break;
                case 4: command("say 你認為" + msg + "？"); break;
                case 5: command("say 我有同感"); break;
                case 6: command("say 你説的「" + msg + "」我不能苟同"); break;
                case 7: command("say 有關「" + msg + "」的話題到此為止好嗎？");;
                }
        } else {
                switch(random(20)) {
                        case 0: command("say 為什麼説" + msg + "?"); break;
                        case 1: command("say 「" + msg + "」是什麼意思？"); break;
                        case 2: command("say " + msg + "？"); break;
                        case 3: command("grin"); break;
                        case 4: command("smile"); break;
                        case 5: command("?"); break;
                        case 6: command("say ...."); break;
                        case 7: command("hmm"); break;
                        case 8: command("say " + rnd_say[random(sizeof(rnd_say))]); break;
                        case 9: command("say 你怎麼知道" + msg + "?"); break;
                        case 10: command("say 剛剛" + who + "不是説了，" + msg);
                        case 11: command("say 我當然知道，" + msg); break;
                        case 12: command("say 然後呢？"); break;
                        case 13: command("say 真的嗎？"); break;
                        case 14: command("say 我不這麼認為。"); break;
                        default:
                                break;
                }
        }
}

void reset()
{
        delete("memory");
}

int accept_object()
{
        return 1;
}
void init()
{
    object ob;

    ::init();
    if( interactive(ob = this_player()) && !is_fighting() ) {
         remove_call_out("greeting");
         call_out("greeting", 1, ob);
    }
    add_action("do_dajia","hit");
    add_action("do_dajia","fight");
}

void greeting(object ob)
{
    if( !ob || environment(ob) != environment() ) return;
    say( "桃谷六仙爭先恐後地招呼：過來和我們六兄弟喝酒！\n");
    message_vision("桃幹仙，斜了$N一眼，突然大喊起來：“快拿酒來！”\n", ob);
    message_vision("桃枝仙拍着桌子，喊道：“老子今天要一邊喝酒，一邊看着人
把$N分成九塊！\n", ob);
    message_vision("桃葉仙跳了過來，一把抓住$N，嚷道：我第一！我第一！\n", ob);
    say("桃花仙橫着短棍進來，一屁股坐下，提酒就喝。\n");
    message_vision("桃實仙衝着$N擠擠橘皮老臉，一串串酒嗝衝着$N直冒。\n", ob);
}

int do_dajia()
{
    object ob;

    ob = this_player();
    message_vision("桃谷六仙一擁而上，提起老拳將$N一頓臭打！\n",ob);
    message_vision("$N躺在地上，大叫＂桃谷六爺爺，六位大英雄饒命！＂桃谷六仙六張\n",ob);
    message_vision("皮老臉頓時都露出笑容：＂$N有眼光，是個大好人，收手了不打了！\n",ob);
    set("qi", 10, ob);
    return 1;
}
int do_kill()
{
    object ob;
    ob = this_player();
    message_vision("桃谷六仙一擁而上，提起老拳將$N往死裏打！桃根仙和桃幹仙，桃枝\n",ob);
    message_vision("仙，桃葉仙分抓$N四肢，只聽得一聲慘呼，滿地鮮血內臟，桃谷四仙\n",ob);
    message_vision("竟把$N活生生撕成四片，桃花仙和桃實仙守在旁邊，別人都救護不了！\n",ob);
    ob->die();
    return 1;
}
