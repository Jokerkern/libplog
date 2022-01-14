<template>
  <div class="Setting">
    <SideMenu class="Setting-left"></SideMenu>
    <div class="Setting-right">
      <el-collapse v-model="activeNames">
        <el-collapse-item title="浏览器" name="1">
          <el-form
            ref="form"
            :model="form"
            label-width="150px"
            style="width: 400px"
          >
            <el-form-item label="webSocket ip">
              <el-input v-model="form.websocketIp"></el-input>
            </el-form-item>
            <el-form-item label="webSocket 端口">
              <el-input v-model="form.websocketPort"></el-input>
            </el-form-item>
          </el-form>
        </el-collapse-item>
        <el-collapse-item title="配置" name="2">
          <el-form
            ref="form"
            :model="form"
            label-width="170px"
            style="width: 400px"
          >
            <el-form-item label="模式(1-tcp 2-ws 4-file)">
              <el-input v-model="setting.MODE"></el-input>
            </el-form-item>
            <el-form-item label="缓存日志条数">
              <el-input v-model="setting.BUFFERSIZE"></el-input>
            </el-form-item>
            <el-form-item label="本地存储文件数量">
              <el-input v-model="setting.MAXFILES"></el-input>
            </el-form-item>
            <el-form-item label="本地存储文件大小(M)">
              <el-input v-model="setting.MAXSIZE"></el-input>
            </el-form-item>
            <el-form-item label="归集服务器ip">
              <el-input v-model="setting.TCPIP"></el-input>
            </el-form-item>
            <el-form-item label="归集服务器sinkPort">
              <el-input v-model="setting.TCPSINKPORT"></el-input>
            </el-form-item>
            <el-form-item label="归集服务器httpPort">
              <el-input v-model="setting.TCPHTTPPORT"></el-input>
            </el-form-item>
          </el-form>
        </el-collapse-item>
      </el-collapse>
      <el-button type="primary" @click="onSubmit">确定</el-button>
      <el-button>重置</el-button>
    </div>
  </div>
</template>

<script>
import SideMenu from "./SideMenu.vue";
import "echarts/lib/component/title";
export default {
  name: "Setting",
  components: {
    SideMenu,
  },

  data() {
    return {
      activeNames: ["1", "2"],
      form: {
        websocketIp: "",
        websocketPort: "",
      },
      setting: {
        BUFFERSIZE: "",
        MAXFILES: "",
        MAXSIZE: "",
        MODE: "",
        TCPHTTPPORT: "",
        TCPIP: "",
        TCPSINKPORT: "",
      },
    };
  },
  mounted() {
    this.form.websocketIp = localStorage.getItem("websocketIp")
      ? localStorage.getItem("websocketIp")
      : window.location.hostname;
    this.form.websocketPort = localStorage.getItem("websocketPort")
      ? localStorage.getItem("websocketPort")
      : "9002";
      const that = this;
      this.timer = setTimeout(function() {
        that.setting = JSON.parse(localStorage.getItem("setting"));
      }, 100);
    
  },
  methods: {
    onSubmit() {
      localStorage.clear();
      localStorage.setItem("websocketIp", this.form.websocketIp);
      localStorage.setItem("websocketPort", this.form.websocketPort);
      let ws = this.$store.state.webSocket;
      ws.send(JSON.stringify(this.setting));
      //this.$store.commit("clear");
      this.$router.replace("/About");
      location.reload();
    },
  },
};
</script>

<style lang="stylus" scoped>
.Setting {
  // 使用flex布局 菜单居左固定宽度 右侧内容区域自适应宽度
  display: flex;

  .Setting-left {
    box-sizing: border-box;
  }

  .Setting-right {
    box-sizing: border-box;
    width: calc(100% - 200px);
    padding: 8px 24px;
    flex: 1;
  }
}
</style>