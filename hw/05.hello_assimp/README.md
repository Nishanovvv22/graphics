# 🛠️ 빌드에 필요한 패키지


## 🛠️ pkg-config 설치하기

`pkg-config`는 Linux 및 macOS 환경에서 **GLEW, GLFW, Assimp** 등의 외부 라이브러리의 *include 경로* 및 *라이브러리 링크 옵션*을 손쉽게 확인할 수 있도록 도와주는 도구입니다.

이 프로젝트에서는 `Makefile`에서 `pkg-config`를 사용하므로, `make` 명령을 통한 프로젝트 빌드 전에 반드시 `pkg-config`를 설치해야 합니다.

---

### 📌 Ubuntu에서 설치하기

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




## 📦 Assimp

[**Assimp**](https://github.com/assimp/assimp)는 그래픽스 프로그래밍에서 장면(scene) 구성에 필요한 다양한 에셋(예: 삼차원 모델, 텍스처 등)을 손쉽게 불러오고(import), 저장하고(export) 변환하는 기능을 제공하는 **C/C++ 라이브러리**입니다.

본 프로젝트에서는 **Assimp 개발자용 라이브러리**를 이용하여 3D 모델 데이터를 불러오고 렌더링에 활용합니다. 따라서, 프로그램을 빌드하기 전에 아래 명령어를 실행하여 **`libassimp-dev` 패키지를 설치**해야 합니다.

---

### 🖥️ Ubuntu에서 설치하기  

Ubuntu 환경에서는 다음 명령어를 실행하여 `libassimp-dev` 패키지를 설치할 수 있습니다:

```bash
sudo apt update
sudo apt install libassimp-dev
```

설치가 완료되면 `pkg-config`를 이용하여 Assimp 라이브러리가 정상적으로 설치되었는지 확인할 수 있습니다:

```bash
pkg-config --modversion assimp
```

위 명령어를 실행했을 때 **버전 정보(예: 5.2.5)**가 출력되면 설치가 정상적으로 완료된 것입니다. 🚀

---

✅ **이제 Assimp를 활용하여 프로젝트를 빌드할 준비가 되었습니다!**



