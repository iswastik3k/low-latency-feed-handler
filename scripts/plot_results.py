import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("reports/results.csv")

latency = df[df["benchmark"] == "latency"]["value"].values[0]
throughput = df[df["benchmark"] == "throughput"]["value"].values[0]
jitter_min = df[df["benchmark"] == "jitter_min"]["value"].values[0]
jitter_avg = df[df["benchmark"] == "jitter_avg"]["value"].values[0]
jitter_max = df[df["benchmark"] == "jitter_max"]["value"].values[0]

fig, ax1 = plt.subplots(figsize=(9,6))

# Left axis: latency + jitter (ns)
ax1.set_ylabel("Latency / Jitter (ns)", color="blue", fontsize=12)
bars1 = ax1.bar(["Latency", "Jitter Min", "Jitter Avg", "Jitter Max"],
                [latency, jitter_min, jitter_avg, jitter_max],
                color=["blue","lightgreen","green","darkgreen"], alpha=0.6, label="Latency/Jitter")
ax1.tick_params(axis="y", labelcolor="blue")
ax1.grid(axis="y", linestyle="--", alpha=0.7)

# Annotate latency/jitter bars
for bar in bars1:
    height = bar.get_height()
    ax1.annotate(f"{height:.0f} ns",
                 xy=(bar.get_x() + bar.get_width()/2, height),
                 xytext=(0,5), textcoords="offset points",
                 ha="center", va="bottom", fontsize=9, color="blue")

# Right axis: throughput (ticks/sec) as bar
ax2 = ax1.twinx()
ax2.set_ylabel("Throughput (ticks/sec)", color="red", fontsize=12)
bars2 = ax2.bar(["Throughput"], [throughput],
                color="red", alpha=0.7, label="Throughput")
ax2.tick_params(axis="y", labelcolor="red")

# Annotate throughput bar
for bar in bars2:
    height = bar.get_height()
    ax2.annotate(f"{height:.2e}",
                 xy=(bar.get_x() + bar.get_width()/2, height),
                 xytext=(0,5), textcoords="offset points",
                 ha="center", va="bottom", fontsize=9, color="red")

# Title & legend
plt.title("Latency, Jitter, and Throughput (Dual‑Axis)", fontsize=14, fontweight="bold")
fig.legend(loc="upper left", bbox_to_anchor=(0.1,0.9), fontsize=10)

plt.tight_layout()
plt.savefig("reports/plots/latency_jitter_throughput_dual_axis_bar.png")
plt.close()