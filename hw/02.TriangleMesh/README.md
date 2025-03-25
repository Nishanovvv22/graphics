# 🚀 빌드에 필요한 패키지

컴퓨터그래픽스 프로젝트를 빌드하기 위해 필요한 패키지를 설치하는 방법을 정리하였습니다.

---

## 🛠️ pkg-config 설치하기

`pkg-config`는 Linux 및 macOS 환경에서 **GLEW, GLFW, Assimp** 등의 외부 라이브러리의 *include 경로* 및 *라이브러리 링크 옵션*을 손쉽게 확인할 수 있도록 도와주는 도구입니다.

이 프로젝트에서는 `Makefile`에서 `pkg-config`를 사용하므로, `make` 명령을 통한 프로젝트 빌드 전에 반드시 `pkg-config`를 설치해야 합니다.

---

## 📌 Ubuntu에서 설치하기

Ubuntu 환경에서는 다음 명령어를 사용하여 `pkg-config`를 설치할 수 있습니다.

```sh
sudo apt install pkg-config
```

---

## 📜 설치 확인 방법

설치가 완료되었는지 확인하려면 다음 명령어를 입력하세요.

```sh
pkg-config --version
```

출력된 버전 정보가 표시되면 정상적으로 설치된 것입니다. 🎉

---

## 🎯 추가 정보

더 자세한 내용은 [pkg-config 공식 문서](https://www.freedesktop.org/wiki/Software/pkg-config/)에서 확인할 수 있습니다.


