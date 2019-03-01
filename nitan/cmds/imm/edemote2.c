// edemote.c
// updated by doing

inherit F_CLEAN_UP;

int in_use;

int main(object me, string arg)
{
        mapping emote;
        int i;

        if (! SECURITY_D->valid_grant(me, "(immortal)"))
                return 0;

        seteuid(getuid());

        if (! VERSION_D->is_release_server())
                return notify_fail("只有版本發布站點才能修改表情動詞。\n");

        if (! arg) return notify_fail("你要編輯什麼 emote？\n");

        if (sscanf(arg, "-d %s", arg))
        {
                write("刪除 emote：" + arg + "\n");
                EMOTE_D->delete_emote(arg);
                return 1;
        }

        if (sscanf(arg, "-p %s", arg))
        {
                        if (! mapp(emote = EMOTE_D->query_emote(arg)) ||
                    ! sizeof(emote))
                {
                        write("沒有這個表情動詞。\n");
                        return 1;
                }

                write(sprintf("上次修改：%s(%s)\n", emote["updated"], ctime(emote["time"])));
                write(sprintf("─────────────────────\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                      emote["myself"], emote["others"], emote["myself_self"],
                      emote["others_self"], emote["myself_target"], emote["target"],
                      emote["others_target"]));
                return 1;
        }

        write(sprintf("arg = %s\n", arg));
        for (i = 0; i < strlen(arg); i++)
                if (arg[i] <= 32 || arg[i] > 'z')
                        return notify_fail("表情動詞必須由字母或數字、標點構成。\n");

        emote = EMOTE_D->query_emote(arg);
        if (! mapp(emote)) emote = ([ ]);

        emote["updated"] = geteuid(me);

        write("編輯 emote：" + arg + "\n");
        write("訊息可以有好幾行，用 . 表示結束。\n"
              "輸入 x 表示該行採用同一族類似的表情描述。\n");
        write("訊息中可使用的參數有以下幾種：\n");
        write("  $N  自己的名字。\n");
        write("  $n  使用對象的名字。\n");
        write("  $P  自己的人稱代名詞，如你、你、他、她、它、它。\n");
        write("  $p  使用對象的人稱代名詞，如你、你、他、她、它、它。\n");
        write("  $S  對自己的稱呼。\n");
        write("  $s  對自己的粗魯稱呼。\n");
        write("  $C  對自己的呢稱。\n");
        write("  $c  對別人的呢稱。\n");
        write("  $R  對別人的尊稱。\n");
        write("  $r  對別人的粗魯稱呼。\n");
        write("────────────────────────────────────\n");
        write("不指定對象使用這個 emote 時，你自己看到的訊息：\n->");
        input_to("get_msg_myself", emote, arg);
        return 1;
}


int get_msg_myself(string msg, mapping emote, string pattern, int n)
{
        msg = replace_string(msg, "\\n", "\n");
        if (msg == "." || msg == "x")
        {
                if (msg == "x")
                        map_delete(emote, "myself");
                else
                if (! n) write("忽略該項描述。\n");
                write("不指定對象使用這個 emote 時，其他人看到的訊息：\n->");
                input_to("get_msg_others", emote, pattern);
                return 1;
        }

        if (! n) map_delete(emote, "myself");
        if (! undefinedp(emote["myself"]))
                emote["myself"] += msg + "\n";
        else emote["myself"] = msg + "\n";
        write("->");
        input_to("get_msg_myself", emote, pattern, n + 1);
        return 1;
}

int get_msg_others(string msg, mapping emote, string pattern, int n)
{
        msg = replace_string(msg, "\\n", "\n");
        if (msg == "." || msg == "x")
        {
                if (msg == "x")
                        map_delete(emote, "others");
                else
                if (! n) write("忽略該項描述。\n");
                write("對自己使用這個 emote 時，自己看到的訊息：\n->");
                input_to("get_msg_myself_self", emote, pattern);
                return 1;
        }

        if (! n) map_delete(emote, "others");
        if (! undefinedp(emote["others"]))
                emote["others"] += msg + "\n";
        else emote["others"] = msg + "\n";
        write("->");
        input_to("get_msg_others", emote, pattern, n + 1);
        return 1;
}

int get_msg_myself_self(string msg, mapping emote, string pattern, int n)
{
        msg = replace_string(msg, "\\n", "\n");
        if (msg == "." || msg == "x")
        {
                if (msg == "x")
                        map_delete(emote, "myself_self");
                else
                if (! n) write("忽略該項描述。\n");
                write("對自己使用這個 emote 時，其他人看到的訊息：\n->");
                input_to("get_msg_others_self", emote, pattern);
                return 1;
        }

        if (! n) map_delete(emote, "myself_self");
        if (! undefinedp(emote["myself_self"]))
                emote["myself_self"] += msg + "\n";
        else emote["myself_self"] = msg + "\n";
        write("->");
        input_to("get_msg_myself_self", emote, pattern, n + 1);
        return 1;
}

int get_msg_others_self(string msg, mapping emote, string pattern, int n)
{
        msg = replace_string(msg, "\\n", "\n");
        if (msg == "." || msg == "x")
        {
                if (msg == "x")
                        map_delete(emote, "others_self");
                else
                if (! n) write("忽略該項描述。\n");
                write("對別人使用這個 emote 時，自己看到的訊息：\n->");
                input_to("get_msg_myself_target", emote, pattern);
                return 1;
        }

        if (! n) map_delete(emote, "others_self");
        if (! undefinedp(emote["others_self"]))
                emote["others_self"] += msg + "\n";
        else emote["others_self"] = msg + "\n";
        write("->");
        input_to("get_msg_others_self", emote, pattern, n + 1);
        return 1;
}

int get_msg_myself_target(string msg, mapping emote, string pattern, int n)
{
        msg = replace_string(msg, "\\n", "\n");
        if (msg == "." || msg == "x")
        {
                if (msg == "x")
                        map_delete(emote, "myself_target");
                else
                if (! n) write("忽略該項描述。\n");
                write("對別人使用這個 emote 時，使用對象看到的訊息：\n->");
                input_to("get_msg_target", emote, pattern);
                return 1;
        }

        if (! n) map_delete(emote, "myself_target");
        if (! undefinedp(emote["myself_target"]))
                emote["myself_target"] += msg + "\n";
        else emote["myself_target"] = msg + "\n";
        write("->");
        input_to("get_msg_myself_target", emote, pattern, n + 1);
        return 1;
}

int get_msg_target(string msg, mapping emote, string pattern, int n)
{
        msg = replace_string(msg, "\\n", "\n");
        if (msg == "." || msg == "x")
        {
                if (msg == "x")
                        map_delete(emote, "target");
                else
                if (! n) write("忽略該項描述。\n");
                write("對別人使用這個 emote 時，除你自己和使用對象外，其他人看到的訊息：\n->");
                input_to("get_msg_others_target", emote, pattern);
                return 1;
        }

        if (! n) map_delete(emote, "target");
        if (! undefinedp(emote["target"]))
                emote["target"] += msg + "\n";
        else emote["target"] = msg + "\n";
        write("->");
        input_to("get_msg_target", emote, pattern, n + 1);
        return 1;
}

int get_msg_others_target(string msg, mapping emote, string pattern, int n)
{
        msg = replace_string(msg, "\\n", "\n");
        if (msg == "." || msg == "x")
        {
                if (msg == "x")
                        map_delete(emote, "others_target");
                else
                if (! n) write("忽略該項描述。\n");
                emote["time"] = time();
                EMOTE_D->set_emote(pattern, emote);
                write("Emote 編輯結束。\n");
                return 1;
        }

        if (! n) map_delete(emote, "others_target");
        if (! undefinedp(emote["others_target"]))
                emote["others_target"] += msg + "\n";
        else emote["others_target"] = msg + "\n";
        write("->");
        input_to("get_msg_others_target", emote, pattern, n + 1);
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : edemote [-d|-p] <emote>

這個指令可以修改，刪除 emote 或列出其內容。 加上 -d 參數會刪
除指定的 emote，-p 參數則會列出指定 emote 的內容. 列出的順序
與編輯 emote 時相同.
 
輸入 emote 訊息時有三個項目：沒有目標， 指定目標或是對自己。
若不想修改某項訊息，則直接在空白行輸入 '.' 跳過.
 
一個 emote 訊息可以有很多行, 在空白行輸入 '.' 表示結束輸入該
項 emote.
 
編輯 emote 時可以用以下的符號來表示:
 
$N : 自己的名字.
$n : 目標的名字.
$P : 自己的人稱代名詞.
$p : 目標的人稱代名詞.
$S : 對自己的稱呼。
$s : 對自己的粗魯稱呼。
$C : 對自己的呢稱。
$c : 對別人的呢稱。
$R : 對別人的尊稱。
$r : 對別人的粗魯稱呼。

由于表情動詞會在版本同步時更新，因此只有版本發布站點才能夠使
用這個命令。

see also：edemote、rnemote
HELP );
    return 1;
}