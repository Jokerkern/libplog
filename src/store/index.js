import Vue from 'vue'
import Vuex from 'vuex'
import 'es6-promise/auto'
Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    log: [],
    total: 0,
    monthTotal: [0,0,0,0,0,0,0,0,0,0,0,0],
    levelTotal: [0, 0, 0, 0],
    fileTotal: [],
    webSocket: WebSocket,
    setting: {},
  },
  getters: {
    log: (state) => state.log,
    total: (state) => state.total,
    monthTotal: (state) => state.monthTotal,
    levelTotal: (state) => state.levelTotal,
    fileTotal: (state) => state.fileTotal,
    webSocket: (state) => state.webSocket,
    setting: (state) => state.setting,
  },
  mutations: {
    changeLog(state, data) {
      state.log.push(data);
    },
    changeLogContent(state, data) {
      state.log[data.logIndex].content.unshift(data.log);
    },
    changeTotal(state) {
      state.total += 1;
    },
    changeMonthTotal(state, data) {
      state.monthTotal[data]++;
    },
    changeLevelTotal(state, data) {
      state.levelTotal[data]++;
    },
    changeFile(state, data) {
      state.fileTotal.push(data);
    },
    changeFileTotal(state, data) {
      state.fileTotal[data].total++;
    },
    changeWebSocket(state, data) {
      state.webSocket = data;
    },
    changeSetting(state, data) {
      state.setting = data;
    },
    clear(state) {
      state.log= [];
      state.total= 0;
      state.monthTotal= [0,0,0,0,0,0,0,0,0,0,0,0];
      state.levelTotal= [0, 0, 0, 0];
      state.fileTotal= [];
      state.webSocket= null;
      state.setting = {};
    },
  },
  actions: {
  },
  modules: {
  }
})
